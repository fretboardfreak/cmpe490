#include <stdio.h>

int main (int argc, char** argv)
{
  FILE * infile;
  FILE * outfile;
  char inbuff[2] = {0,0};
  char outbuff[3] = {0,0,0};

  infile = fopen(argv[1],"rb");
  outfile = fopen (argv[2],"wb");

  while( fread(inbuff, 2, 1, infile) == 1 )
    {
      outbuff[0] = inbuff[0] & 0xf8;
      outbuff[1] = (inbuff[0] & 0x7)<<5 | (inbuff[1] & 0xe0)>>5;
      outbuff[2] = (inbuff[1] & 0x1f)<<3;
      fwrite(outbuff, 3, 1, outfile);
    }
  fclose(infile);
  fclose(outfile);
  return 1;
}

  /*11111000 00011111*/
  /* 0xf800, 0x7e00, 0x1f*/
