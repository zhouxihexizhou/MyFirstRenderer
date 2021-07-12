#include"effect.h"
#include <fstream>
#include <io.h>
#include <png.h>


//��ȡ����ͼƬ
void getAllTex(string path, vector<string>& files, string fileType, vector<string>& fileName)
{
    // �ļ����
    long hFile = 0;
    // �ļ���Ϣ
    struct _finddata_t fileinfo;

    string p;

    if ((hFile = _findfirst(p.assign(path).append("\\*" + fileType).c_str(), &fileinfo)) != -1) {
        do {
            //�����ļ���ȫ·��
            files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            fileName.push_back(fileinfo.name);

        } while (_findnext(hFile, &fileinfo) == 0); //Ѱ����һ�����ɹ�����0������-1

        _findclose(hFile);
    }
}


//��ȡ��ͼ����
void getTexBuff(string path, string name)
{
    int width, height;

    FILE* fp;
    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep* row_pointers;
    unsigned char* buff;

    int x, y;

    fp = fopen(path.c_str(), "rb");
    if (fp == NULL) {
        printf("ͼƬ��ȡʧ��");
        return;
    }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info_ptr = png_create_info_struct(png_ptr);

    //��λ�ļ�ָ��
    rewind(fp);
    //��ʼ���ļ�
    png_init_io(png_ptr, fp);
    //��ȡPNGͼƬ��Ϣ����������
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, NULL);

    //��ÿ��
    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);

    //��ȡͼ����������������ݣ�row_pointers��߾���rgba����
    row_pointers = png_get_rows(png_ptr, info_ptr);

    int color_type = png_get_color_type(png_ptr, info_ptr);        //���ͼƬ��ɫ����
    int block_size = (color_type == 6 ? 4 : 3);

    //(A)RGB
    int file_size = (width) * (height) * 4;
    buff = new unsigned char[file_size];

    int pos = 0;
    int rot, pre;
    for (x = 0; x < height; x++) {
        for (y = 0; y < width * block_size; y += block_size)
        {
            pre = x * width * block_size;
            rot = pre + (width - 1) * block_size - (pos - pre);
            buff[rot + 0] = row_pointers[x][y + 0];      //R
            buff[rot + 1] = row_pointers[x][y + 1];      //G
            buff[rot + 2] = row_pointers[x][y + 2];      //B
            if (color_type == 6)
                //buff[rot + 3] = row_pointers[x][y + 3];   //A
            //else
                //buff[rot + 3] = 0xff;    //û��͸��ͨ�����ݣ�����䲻͸��0xff
            pos += 3;

            cout << (int)buff[rot + 0] << endl;
            cout << (int)buff[rot + 1] << endl;
            cout << (int)buff[rot + 2] << endl;
            cout << "------------" << endl;
        }
    }
    //�����Ѿ����������ݷ�תȡ��������buff

    fclose(fp);

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
}