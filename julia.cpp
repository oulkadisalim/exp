#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <pthread.h>
#include <unistd.h>



//Constantes taille Julia
#define WIDTH  599
#define HEIGHT 799

//fonction pour le parcours des pixel de l'image
#define fx(x) ((int) ((x + 2)/4.0 * WIDTH))
#define fy(y) ((int) ((2 - y)/4.0 * HEIGHT))
double zoom= 1;
//Association d'un pointeur à une image
IplImage* img_julia;

//Zoom width
long double gx(int i, double zoom)
{
    return ((i)*4.0*zoom/WIDTH);
}

//zoom height
long double gy(int j, double zoom)
{
    return ((j)*4.0*zoom/HEIGHT);
}


//fonction julia
void julia(int it, int pd,long double re, long double im, IplImage* img_julia,double zoom)
{
  uchar *p;
  assert (img_julia->depth == IPL_DEPTH_8U && img_julia->nChannels == 1);
  for (int i = fx(-2.0); i <= fx(2.0); i++)
  {
      for (int j = fy(-2.0); j >= fy(2.0); j--)
      {
          long double x = gx(i,zoom), y = gy(j,zoom), t;
          int k = 0;

          while (x*x + y*y < 4 && k < it)
          {
              t = x*x - y*y + re;
              y = 2*x*y + im;
              x = t;
              k++;
          }
          //p = (int) (k * pd);
          p = cvPtr2D (img_julia, i, j, NULL);
          int z = (k * pd);
          *p = 255 - z*10;
      }
  }
}

//création d'un thread
void *thread_1(void *arg)
{
  long double im = 0.013;
  long double re = 0.285;
  int nb_max_it = 2;
  
	while(true)
	{ 
 
if (0<= zoom){
         julia(nb_max_it,1,re,im,img_julia,zoom);
            zoom = zoom -0.01;
nb_max_it++;
}

 
     
 
	}

}


     void *thread_2(void *arg)
{
  long double im = 0.013;
  long double re = 0.285;
  int nb_max_it = 2;
  
	while(true)
	{ 
 
if (zoom< 0){
         julia(nb_max_it,1,re,im,img_julia,zoom);
            zoom = zoom -0.01;
nb_max_it++;
}

 
     
 
	}

}


 
	





int main(int argc, char *argv[])
{
  //déclaration du thread
  pthread_t thread1;
  pthread_t thread2;
  //création d'une image de 800*600
  img_julia = cvCreateImage (cvSize (800, 600), IPL_DEPTH_8U, 1);
  
  //Couleur
  cvSet(img_julia, cvScalar(94, 206, 165));
   

  //création d'une fenetre 
  cvNamedWindow("Set of Julia By ", CV_WINDOW_AUTOSIZE); 
  cvMoveWindow(" Julia By saibi et oulkadi", 200, 10);

  char key;
  //Appel au thread
 

 
  //création d'une variable pour la récupération des frappes du clavier
  
  	// Affichage de l'image ( chargement de img_julia dans la fenetre )
  	while(true)
  	{
            cvShowImage(" fractale de julia marzouketsalim", img_julia);
   	    key=cvWaitKey(1);

    	    if(key == 'c')
    		{

                pthread_create(&thread1, NULL, thread_1, NULL) ;
	//pthread_cancel(thread2);
    
    		}
    if(key == 'x')
    		{


        pthread_create(&thread2, NULL, thread_2, NULL);

    }
    		

   if(key == 'q')
    		{
           break;
    }

  	}







        return 0;


}



















