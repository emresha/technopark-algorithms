/*
Напишите две функции для создания архива из одного файла и извлечения файла из архива.

Метод архивирует данные из потока original
void Encode(IInputStream& original, IOutputStream& compressed);

Метод восстанавливает оригинальные данные
void Decode(IInputStream& compressed, IOutputStream& original);

В архиве сохраняйте дерево Хаффмана и код Хаффмана от исходных данных.
Дерево Хаффмана требуется хранить эффективно - не более 10 бит на каждый 8-битный символ.

В контест необходимо отправить .cpp файл содержащий функции Encode, Decode, а также включающий файл Huffman.h.
Тестирующая программа выводит размер сжатого файла в процентах от исходного.
*/

// #include "Huffman.h"
#include <bits/stdc++.h>

typedef char byte;

class IInputStream
{
public:
    virtual bool Read(byte &value) = 0;
};

class IOutputStream
{
public:
    virtual void Write(byte value) = 0;
};

class BitWriter
{
    IOutputStream &out;
    unsigned char buffer;
    int count;

public:
    BitWriter(IOutputStream &output) : out(output), buffer(0), count(0) {}

    void write_bit(int bit)
    {
        buffer = buffer << 1 | (bit & 1);
        count++;
        if (count == 8)
        {
            out.Write(buffer);
            buffer = 0;
            count = 0;
        }
    }

    void write_bits(const std::string &bits)
    {
        for (char c : bits)
        {
            if (c == '0')
                write_bit(0);
            else
                write_bit(1);
        }
    }

    void flush(void)
    {
        if (count > 0)
        {
            buffer = buffer << (8 - count);
            out.Write(buffer);
            buffer = 0;
            count = 0;
        }
    }
};

class BitReader
{
    IInputStream &in;
    char buffer;
    int count;
    bool eof;

public:
    BitReader(IInputStream &input) : in(input), buffer(0), count(0), eof(false) {}

    int read_bit(void)
    {
        if (count == 0)
        {
            if (!in.Read((byte &)buffer))
            {
                eof = true;
                return -1;
            }
            count = 8;
        }
        int bit = (buffer >> (count - 1)) & 1;
        count--;
        return bit;
    }

    std::string read_bits(int n)
    {
        std::string bits = "";
        for (int i = 0; i < n; ++i)
        {
            int bit = read_bit();
            if (bit == -1)
                break;
            bits += std::to_string(bit);
        }
        return bits;
    }
};

struct HuffmanNode
{
    byte value;
    int freq;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(byte val, int frequency)
    {
        value = val;
        freq = frequency;
        left = nullptr;
        right = nullptr;
    }
    HuffmanNode(HuffmanNode *l, HuffmanNode *r) : value(0), freq(l->freq + r->freq), left(l), right(r) {}
};

struct CompareNode
{
    bool operator()(HuffmanNode *a, HuffmanNode *b)
    {
        return a->freq > b->freq;
    }
};

HuffmanNode *build_huffman(const std::vector<int> &freq)
{
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, CompareNode> pq;

    for (int i = 0; i < 256; ++i)
    {
        if (freq[i] > 0)
        {
            pq.push(new HuffmanNode((byte)(i), freq[i]));
        }
    }

    if (pq.size() == 1)
    {
        HuffmanNode *onlyNode = pq.top();
        pq.pop();
        pq.push(new HuffmanNode(onlyNode, new HuffmanNode(0, 0)));
    }

    while (pq.size() > 1)
    {
        HuffmanNode *left = pq.top();
        pq.pop();
        HuffmanNode *right = pq.top();
        pq.pop();
        HuffmanNode *merged = new HuffmanNode(left, right);
        pq.push(merged);
    }

    if (pq.empty())
        return nullptr;

    return pq.top();
}

void generate_codes(HuffmanNode *node, std::string current, std::vector<std::string> &codes)
{
    if (!node)
        return;
    
    if (!node->left && !node->right)
    {
        codes[(unsigned char)(node->value)] = current.empty() ? "0" : current;
    }

    generate_codes(node->left, current + "0", codes);
    generate_codes(node->right, current + "1", codes);
}

void tree_serialize(HuffmanNode *node, BitWriter &bw)
{
    if (!node->left && !node->right)
    {
        bw.write_bit(1);
        for (int i = 7; i >= 0; --i)
        {
            bw.write_bit((node->value >> i) & 1);
        }
    }
    else
    {
        bw.write_bit(0);
        tree_serialize(node->left, bw);
        tree_serialize(node->right, bw);
    }
}

HuffmanNode *tree_deserialize(BitReader &br)
{
    int bit = br.read_bit();
    if (bit == -1)
        return nullptr;

    if (bit == 1)
    {
        byte value = 0;
        for (int i = 0; i < 8; ++i)
        {
            int b = br.read_bit();
            if (b == -1)
                break;
            value = (value << 1) | b;
        }
        return new HuffmanNode(value, 0);
    }
    else
    {
        HuffmanNode *left = tree_deserialize(br);
        HuffmanNode *right = tree_deserialize(br);
        return new HuffmanNode(left, right);
    }
}

void delete_huffman(HuffmanNode *node)
{
    if (!node)
        return;
    delete_huffman(node->left);
    delete_huffman(node->right);
    delete node;
}

void Encode(IInputStream &original, IOutputStream &compressed)
{
    std::vector<int> freq(256, 0);
    std::vector<byte> data;
    byte byteValue;
    while (original.Read(byteValue))
    {
        data.push_back(byteValue);
        freq[(unsigned char)(byteValue)]++;
    }

    HuffmanNode *root = build_huffman(freq);
    if (!root)
        return;

    std::vector<std::string> codes(256, "");
    generate_codes(root, "", codes);

    BitWriter bw(compressed);
    tree_serialize(root, bw);

    for (byte b : data)
    {
        bw.write_bits(codes[(unsigned char)(b)]);
    }

    bw.flush();

    delete_huffman(root);
}

void Decode(IInputStream &compressed, IOutputStream &original)
{
    BitReader br(compressed);
    HuffmanNode *root = tree_deserialize(br);
    if (!root)
        return;

    HuffmanNode *current = root;
    int bit;
    while ((bit = br.read_bit()) != -1)
    {
        if (bit == 0)
        {
            if (current->left)
                current = current->left;
            else
                break;
        }
        else
        {
            if (current->right)
                current = current->right;
            else
                break;
        }

        if (!current->left && !current->right)
        {
            original.Write(current->value);
            current = root;
        }
    }

    delete_huffman(root);
}
