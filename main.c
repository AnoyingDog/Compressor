#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<libavformat/avformat.h>

void ErrorMessage(){
    printf("\nPass in the Input File, Target Size (in MB), AudioBitrate (0-128 the higher the value the higher the audio quality.) and Output File\n");
    printf("As example: compressor input.mp4 10 128 output.mp4\n\n");
}

int main(int argc, char *argv[]){

  if(argc != 5){
    ErrorMessage();
    return EXIT_FAILURE;
  }

  double TargetBitrate;
  char *Filename = argv[1];
  int VideoBitrate, AudioBitrate = strtol(argv[3], NULL, 10);
  char *OutputFilename = argv[4];
  int TargetFileSize = strtol(argv[2], NULL, 10);

  if(AudioBitrate >= 128){
    AudioBitrate = 128;
  }

  //Getting the Video Length in Seconds
  AVFormatContext *fmt_ctx = NULL;

  if (avformat_open_input(&fmt_ctx, argv[1], NULL, NULL) != 0) {
    printf("File not found/read access denied.\n");
    ErrorMessage();
    return EXIT_FAILURE;
  }
  if (avformat_find_stream_info(fmt_ctx, NULL) < 0) {
    printf("Could not find stream info.\n");
    ErrorMessage();
    return EXIT_FAILURE;
  }


  double VideoLengthSec = (double)fmt_ctx->duration / AV_TIME_BASE;
  //printf("Video Duration: %.2f seconds\n", VideoLengthSec);
  
  //Calculates bitrate
  TargetBitrate = TargetFileSize * 8000;
  TargetBitrate = TargetBitrate/VideoLengthSec;
  VideoBitrate = TargetBitrate - AudioBitrate;

  char* FinalCommand;
  asprintf(&FinalCommand, "ffmpeg -i %s -b:v %dk -b:a %dk -preset slow %s\n", Filename, VideoBitrate, AudioBitrate, OutputFilename);
  system(FinalCommand);


  return EXIT_SUCCESS;
}
