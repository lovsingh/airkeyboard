#include <highgui.h>
#include <cv.h>
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
int key_value[6][11];
void keyboard();
void main( )
{
int max_buffer=0,i,j=0,k=0,pen_pixels=0,loc=0,loc1=0,counter,init=0,real=0;
int tip_x=0,tip_y=0,last_x=0,last_y=0,frame=0;
char c;
HWND stealth;
CvLineIterator iterator;
CvCapture*capture=cvCaptureFromCAM(-1);  
cvNamedWindow("Video",CV_WINDOW_AUTOSIZE);
keyboard();
AllocConsole();
stealth=FindWindowA("ConsoleWindowClass",NULL);
ShowWindow(stealth,0);
while(1)
{
IplImage *im_rgb = cvQueryFrame(capture);
IplImage *im_gray = cvCreateImage(cvGetSize(im_rgb),IPL_DEPTH_8U,1);
IplImage *im_bw = cvCreateImage(cvGetSize(im_gray),IPL_DEPTH_8U,1);
if(!im_rgb)
{
printf("Camera not found.Check your camera connection");
break;
}
cvWaitKey(20);
frame=frame+1;
tip_x=0;
tip_y=0;
cvCvtColor(im_rgb,im_gray,CV_RGB2GRAY);                                          cvThreshold(im_gray, im_bw,128,255 , CV_THRESH_BINARY | CV_THRESH_OTSU);
cvLine(im_rgb,cvPoint(10,10), cvPoint(340,10),CV_RGB(255,0,0 ),4,8,0);   cvLine(im_rgb,cvPoint(10,10), cvPoint(10,185),CV_RGB(255,0,0 ),4,8,0);
cvLine(im_rgb,cvPoint(340,10), cvPoint(340,185),CV_RGB(255,0,0 ),4,8,0);
for(i=1;i<=10;i++)
{
cvLine(im_rgb,cvPoint(i*34,10), cvPoint(i*34,185),CV_RGB(255,0,0 ),1,8,0);
}
for(i=1;i<=5;i++)
{
cvLine(im_rgb,cvPoint(11,(i*34)+11), cvPoint(340,(i*34)+11),CV_RGB(255,0,0 ),1,8,0);
}
for(k=20;k<185;k++)
{
pen_pixels=0;
counter=0;
init=0;
max_buffer = cvInitLineIterator(im_bw,cvPoint(11,k),cvPoint(170,k),&iterator,8,0);
for(j=0; j<max_buffer; j++)
{
if(iterator.ptr[j]==0)
{
loc1=j+11;
if((loc1-loc)==1)
{
if(counter==0)
{
init=loc1-1;
counter++;
}
pen_pixels=pen_pixels+1;
}
}
loc=loc1;
CV_NEXT_LINE_POINT(iterator);
}
if(pen_pixels>6&&pen_pixels<25)
{
cvCircle(im_rgb, cvPoint(init*2,k),10,CV_RGB(255,0,0 ) ,2,8,0);  		               tip_x=init*2;
tip_y=k+18;
}
}
cvCircle(im_rgb, cvPoint(tip_x,tip_y),10,CV_RGB(0,255,0 ) ,2,8,0);  		tip_x=tip_x/34;
tip_y=tip_y/34;
if(frame==5)
{
frame=0;
if((last_x==tip_x)&&(last_y==tip_y))
{
keybd_event(key_value[tip_y][tip_x+1],0x45,0,0);   			frame=0;
}
}
if(frame==1)
{
last_x=tip_x;
last_y=tip_y;
}
cvShowImage("Video", im_rgb);
c = cvWaitKey(1);
if(c==27)
break;
}

cvReleaseCapture(&capture);
cvDestroyWindow("Video");
//cvDestroyWindow("Video1");
}
void keyboard()
{
key_value[1][1]=0x08;
key_value[1][2]=0x08;
key_value[1][3]=0x08;
key_value[1][4]=0x4E;
key_value[1][5]=0x20;
key_value[1][6]=0x20;
key_value[1][7]=0x20;
key_value[1][8]=0x14;
key_value[1][9]=0x14;
key_value[1][10]=0x14;

key_value[2][1]=0x1B;
key_value[2][2]=0x4E;
key_value[2][3]=0x4E;
key_value[2][4]=0x4D;
key_value[2][5]=0x4E;
key_value[2][6]=0x42;
key_value[2][7]=0x56;
key_value[2][8]=0x43;
key_value[2][9]=0x58;
key_value[2][10]=0x5A;

key_value[3][1]=0x0D;
key_value[3][2]=0x4C;
key_value[3][3]=0x4B;
key_value[3][4]=0x4A;
key_value[3][5]=0x48;
key_value[3][6]=0x47;
key_value[3][7]=0x46;
key_value[3][8]=0x44;
key_value[3][9]=0x53;
key_value[3][10]=0x41;

key_value[4][1]=0x50;
key_value[4][2]=0x4F;
key_value[4][3]=0x49;
key_value[4][4]=0x55;
key_value[4][5]=0x59;
key_value[4][6]=0x54;
key_value[4][7]=0x52;
key_value[4][8]=0x45;
key_value[4][9]=0x57;
key_value[4][10]=0x51;

key_value[5][1]=0x30;
key_value[5][2]=0x39;
key_value[5][3]=0x38;
key_value[5][4]=0x37;
key_value[5][5]=0x36;
key_value[5][6]=0x35;
key_value[5][7]=0x34;
key_value[5][8]=0x33;
key_value[5][9]=0x32;
key_value[5][10]=0x31;

}
