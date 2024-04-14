#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;


// Sectoin 25 & 26

/*
This file includes 8 filters to perform on images :
     1: Rotate                  Yousef Okasha     : 20231213
     2: Frame                   Yousef Okasha     : 20231213
     3: Invert                  Yousef Okasha     : 20231213
     4: Blur                    Yousef Okasha     : 20231213
     5: Black and white         Ahmed Al-Hassan   : 20231004
     6: Flip                    Ahmed Al-Hassan   : 20231004
     7: Crop                    Ahmed Al-Hassan   : 20231004
     8: Resize                  Ahmed Al-Hassan   : 20231004
     9: Gray scale              Abdelaziz Mohamed : 20230222
*/

void reverse(Image& photo)
{
    for (int i = 0; i < photo.width / 2; i++)
    {
        for (int j = 0; j < photo.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                unsigned char temp = photo(i, j, k);
                photo(i, j, k) = photo(photo.width - 1 - i, j, k);
                photo(photo.width - 1 - i, j, k) = temp;
            }
        }
    }
}



Image rotate(Image& IMG1)
{
    Image IMG2(IMG1.height,IMG1.width) ;   
        for (int i = 0 ; i < IMG1.width ; i++)
        {
            for (int j = 0 ; j < IMG1.height ; j++)
            {
                for(int k = 0 ; k < 3 ; k++)
                {
                    IMG2(j,i,k) = IMG1(i,j,k) ; 
                    // while j is increasing we are in the first image's columns
                    // on the other hand we are building the new image's row
                } 

            }
        }
        reverse(IMG2);
        return IMG2;
}

void Invert (Image& IMG)
{
    for (int i = 0 ; i < IMG.width ; i++)
    {
        for (int j = 0 ; j < IMG.height ; j++)
        {
            for(int k = 0 ; k < 3 ; k++)
            {
                //Every colour is replaced by its correspondece
                IMG(i,j,k) = abs(IMG(i,j,k) - 255) ;
            } 
        }

    }
}

// Frame size would be 1/24 of the image
void frame(Image& IMG , int R , int G , int B)
{
    //Right side
    for (int i = 0 ; i < IMG.width/24 ; i++)
    {
        for (int j = 0 ; j < IMG.height ; j++)
        {
            IMG(i,j,0) = R ; 
            IMG(i,j,1) = G ; 
            IMG(i,j,2) = B ; 
        }
    }

    //Left Side
    for (int i = IMG.width-1 ; i >= IMG.width*23/24 ; i--)
    {
        for (int j = 0 ; j < IMG.height ; j++)
        {
            IMG(i,j,0) = R ; 
            IMG(i,j,1) = G ; 
            IMG(i,j,2) = B ; 
        }
    }

    //Down side
    for (int i = 0 ; i < IMG.height/24 ; i++)
    {
        for (int j = 0 ; j < IMG.width ; j++)
        {
            IMG(j,i,0) = R ; 
            IMG(j,i,1) = G ; 
            IMG(j,i,2) = B ; 
        }
    }

    // Upper side 
    for (int i = IMG.height-1 ; i >= IMG.height*23/24 ; i--)
    {
        for (int j = 0 ; j < IMG.width ; j++)
        {
            IMG(j,i,0) = R ; 
            IMG(j,i,1) = G ; 
            IMG(j,i,2) = B ; 
        }
    }

}

Image Blur(Image &image)
{
    Image newImage(image.width-50,image.height-50);
	int l = 0;
	cout << "Please wait a couple of minutes\n" ;
	for (int i = 26; i <= image.width-25; i++)
	{
		int m = 0;
		if (i == 1400) 
		{
			cout << "It is almost done ,please wait it takes more time with big sized pictures\n";
		}
		for (int j = 26; j <= image.height-25; j++)
		{
			int Rsum = 0, Gsum = 0, Bsum = 0;
			for (int ctr = i-25; ctr < i+25 ; ctr++)
			{
				for (int ctr2 = j-25; ctr2 < j+25; ctr2++)
				{
				 	Rsum +=image(ctr,ctr2,0) ;
				 	Gsum +=image(ctr,ctr2,1) ;
				 	Bsum +=image(ctr,ctr2,2) ;
				}
			}
				newImage(l,m,0) = Rsum/2601 ;
				newImage(l,m,1) = Gsum/2601 ;
				newImage(l,m,2) = Bsum/2601 ;
			m++;
		}
		l++ ;
	}
    return newImage ;
}

//////////////////////////////////////////////////////////////////////////////

string GetStringMessage(string message) {
  cout << message << "\n";
  string input;
  cin >> input;
  return input;
}
void BlackAndWhite(Image& image) {
  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      unsigned int avg = 0;
      for (int k = 0; k < 3; ++k) {
        avg += image(i, j, k);
      }
      avg /= 3;
      if (avg < 127) {
        image(i, j, 0) = 0;
        image(i, j, 1) = 0;
        image(i, j, 2) = 0;
      } else {
        image(i, j, 0) = 255;
        image(i, j, 1) = 255;
        image(i, j, 2) = 255;
      }
    }
  }
}
void ResultBlackAndWhite() {
  string ImageName = GetStringMessage(
      "Enter colored image name to turn it  to Black and White scale: ");
  Image image(ImageName);
  BlackAndWhite(image);
  string NewImageName =
      GetStringMessage("Enter image name to store new image\nand specify "
                       "extension .jpg, .bmp, .png, .tga: ");
  image.saveImage(NewImageName);
}
// _______________________________
// Fliping(5)
enum enflip { Vertical = 1, Horizontal = 2 };
enflip VerticalOrHorizontal() {
  int choice;
  cout << "1) Vertical\n2) Horizontal\n";
  cin >> choice;
  return (enflip)choice;
}
void FlipVertically(Image &image1, Image &image2) {

  for (int i = 0; i < image1.height; i++) {

    int flippedY = image1.height - 1 - i;

    for (int j = 0; j < image1.width; j++) {

      for (int k = 0; k < image1.channels; k++) {

        image2(j, flippedY, k) = image1(j, i, k);
      }
    }
  }
}
void FlipHorizontally(Image &image1, Image &image2) {

  for (int i = 0; i < image1.height; i++) {

    for (int j = 0; j < image1.width; j++) {

      int mirroredX = image1.width - 1 - j;

      for (int k = 0; k < image1.channels; k++) {

        image2(mirroredX, i, k) = image1(j, i, k);
      }
    }
  }
}
void ResultFlip() {
  string ImageName = GetStringMessage("Enter your image name to flip it :  ");
  Image image(ImageName);
  Image image2(image.width, image.height);
  enflip choice = VerticalOrHorizontal();
  switch (choice) {
  case enflip::Vertical:
    FlipVertically(image, image2);
    break;
  case enflip::Horizontal:
    FlipHorizontally(image, image2);
    break;
  }
  string NewImageName =
    //cout << "Enter image name to store new image\nand specify extension .jpg, .bmp, .png, .tga :  " ;
    GetStringMessage("Enter image name to store new image\nand specify "
                       "extension .jpg, .bmp, .png, .tga :  ");
  image2.saveImage(NewImageName);
}
// ________________________________________
// Croping(8)
int ReadNumberInRange(string message, int min, int max) {
  int number;
  do {
    cout << message;
    cin >> number;
  } while (number < min || number > max);
  return number;
}
Image NewImage(Image image1, Image &image2, int StartWidth, int StartHeight) {
  // Iterate over the dimensions of the new image
  for (int height = 0; height < image2.height; height++) {
    for (int width = 0; width < image2.width; width++) {
      // Calculate the corresponding positions in the source image
      int sourceX = StartWidth + width;
      int sourceY = StartHeight + height;
      // Copy the pixel values from source image to new image
      for (int k = 0; k < 3; k++) {
        image2(width, height, k) = image1(sourceX, sourceY, k);
      }
    }
  }
  return image2;
}
void ResultCrop() {
  string ImageName = GetStringMessage("Enter your image name to crop it : ");
  Image image1(ImageName);
  int StartWidth = ReadNumberInRange(
      "Enter the start width you want to crop from : ", 0, image1.width);
  int StartHeight = ReadNumberInRange(
      "Enter the start height you want to crop from : ", 0, image1.height);
  int NewWidth =
      ReadNumberInRange("Enter the width of new image : ", 0, image1.width);
  int NewHeight =
      ReadNumberInRange("Enter the height of new image : ", 0, image1.height);
  Image image2(NewWidth, NewHeight);
  image2 = NewImage(image1, image2, StartWidth, StartHeight);
  string NewImageName =
      GetStringMessage("Enter image name to store new image\nand specify "
                       "extension .jpg, .bmp, .png, .tga: ");
  image2.saveImage(NewImageName);
}
// __________________________________________
// REsizing(11)
int ReadValue(string message) {
  int value;
  cout << message;
  cin >> value;
  return value;
}
void ResizingImage(Image &OriginalImage, Image &ResizedImage) {
  double width_ratio = double(OriginalImage.width) / ResizedImage.width;
  double height_ratio = double(OriginalImage.height) / ResizedImage.height;

  for (int i = 0; i < ResizedImage.height; i++) {
    for (int k = 0; k < ResizedImage.width; k++) {

      double gwidth = k * width_ratio;
      double gheight = i * height_ratio;

      int gxi = static_cast<int>(gwidth);
      int gyi = static_cast<int>(gheight);

      double frac_width = gwidth - gxi;
      double frac_height = gheight - gyi;

      // Clamp the integer coordinates to avoid out-of-bounds access
      if (gxi < 0)
        gxi = 0;
      if (gyi < 0)
        gyi = 0;
      if (gxi >= OriginalImage.width - 1)
        gxi = OriginalImage.width - 1;
      if (gyi >= OriginalImage.height - 1)
        gyi = OriginalImage.height - 1;

      // Compute the weights for interpolation
      double weight_tl = (1 - frac_width) * (1 - frac_height);
      double weight_tr = frac_width * (1 - frac_height);
      double weight_bl = (1 - frac_width) * frac_height;
      double weight_br = frac_width * frac_height;

      // Perform bilinear interpolation for each channel
      for (int c = 0; c < OriginalImage.channels; c++) {
        double pixel_tl = OriginalImage(gxi, gyi, c);
        double pixel_tr = OriginalImage(gxi + 1, gyi, c);
        double pixel_bl = OriginalImage(gxi, gyi + 1, c);
        double pixel_br = OriginalImage(gxi + 1, gyi + 1, c);

        double new_value = (weight_tl * pixel_tl) + (weight_tr * pixel_tr) +
                           (weight_bl * pixel_bl) + (weight_br * pixel_br);

        ResizedImage(k, i, c) = static_cast<unsigned char>(new_value);
      }
    }
  }
}
void ResultResize() {
  string FileName = GetStringMessage("Enter your image name to resize it : ");
  Image OriginalImage(FileName);
  int NewWidth = ReadValue("Enter the desired width for resizing: ");
  int NewHeight = ReadValue("Enter the desired height for resizing: ");
  Image ResizedImage(NewWidth, NewHeight);
  ResizingImage(OriginalImage, ResizedImage);
  string NewImageName =
      GetStringMessage("Enter image name to store new image\nand specify "
                       "extension .jpg, .bmp, .png, .tga :  ");
  ResizedImage.saveImage(NewImageName);
}


int main() 
{
    string image_name , filter;
    cout << "Welcome to the program\n" ;
    cout << "Please choose a filter (From 1 : 12) to perform :\n" ;
    cout << " 1: Rotate                2: Frame   \n " ;
    cout << "3: Invert                4: Blur      \n " ;
    cout << "5: Black and White       6: Flip       \n ";
    cout << "7: Crop                  8: Resize       \n ";
    cin >> filter ;

    // Validating the choice
    while (stoi(filter) > 12 || stoi(filter) < 1)
    {
        cout << "Invalid choice ,please try again: \n" ;
        cin >> filter ;
    }

    if (stoi(filter)>=1 && stoi(filter) <=4)
    {
        cout << "Enter image's name (INCLUDING THE EXTENTION) : ";
        cin >> image_name ;
        cout << "\n====================\n" ;
        Image Origin(image_name) ;
        string name_save_option ;
        cout << "\n====================\n" ;
        cout << "How do you want to save the photo ? \n" ;
        cout << "1: Save with the same name        2: Enter a new name\n" ;
        cin >> name_save_option ;
        while (name_save_option != "1" && name_save_option != "2")
        {
            cout << "Invalid choice please try again: " ;
            cin >> name_save_option ;
        }
        string full_name ;
        if (name_save_option == "2")
        {
            string new_name , extention ;
            cout << "\nEnter the new name (WITHOUT THE EXTENTION): " ;
            cin >> new_name ;

            cout << "choose an extention: .jpg or .bmp or .png or .tga\n" ;
            cin >> extention;

            // Validating the extention
            while (extention != ".jpg" && extention != ".bmp" && extention != ".png" && extention != ".tga")
            {
                cout << "Invalid extention please try again :\n" ;
                cin >> extention ;
            }
            // Concatinating the name with thr extention to get the full name
            full_name = new_name + extention ;
        }
        else
        {
            full_name = image_name ;   
        }

        if (filter == "1")
        {
            string n ;
            cout << "\n====================\n" ;
            cout << "1: Rotate 90ْ \n2: Rotate 180ْ \n3: Rotate 270ْ \n" ;
            cin >> n ;
            // Validating the choice
            while (n != "1" && n != "2" && n != "3")
            {
                cout << "Invalid choice ,please try again : \n" ;
                cin >> n ;
            }
            if (n == "1")
            {
                cout << "\n====================\n" ;
                cout << "Working on it please wait\n" ;
                Image rotared_90 = rotate(Origin);
                rotared_90.saveImage(full_name) ;
            }
            else if (n == "2")
            {
                // Rotating the image twice to get it 180ْ rotated
                cout << "\n====================\n" ;
                cout << "Working on it please wait\n" ;
                Image rotared_90 = rotate(Origin);
                Image rotared_180 = rotate(rotared_90) ;
                rotared_180.saveImage(full_name) ;
            }
            else 
            {
                // Rotating the image three times to get it 270ْ rotated
                cout << "\n====================\n" ;
                cout << "Working on it please wait\n" ;
                Image rotared_90 = rotate(Origin);
                Image rotared_180 = rotate(rotared_90) ;
                Image rotared_270 = rotate(rotared_180) ;
                rotared_270.saveImage(full_name) ;
            }
        }
        else if (filter == "3")
        {
            Invert(Origin) ;
            Origin.saveImage(full_name) ;

        }
        else if (filter == "2")
        {
            string colour ;
            cout << "Please choose a colour for the frame : \n" ;
            cout << "1: Red         2:Green       3: Blue \n" ;
            cout << "4: Yellow      5:Orange      6: Purple \n" ;
            cin >> colour ;
             while (colour != "1" && colour != "2" &&colour != "3" &&colour != "4" &&colour != "5"&&colour != "6")
            {
                cout << "Invalid choice ,please try again: \n" ;
                cin >> colour ;
            }
            if (colour == "1")
            {
                // To get the red colour
                frame(Origin,200,0,0) ;
                Origin.saveImage(full_name) ;
            }
            else if (colour == "2")
            {
                // To get the green colour
                frame(Origin,0,200,0) ;
                Origin.saveImage(full_name) ;
            }
            else if (colour == "3")
            {
                // To get the blue colour
                frame(Origin,0,0,200) ;
                Origin.saveImage(full_name) ;
            }
            else if (colour == "4")
            {
                // To get the yellow colour
                frame(Origin,200,200,0) ;
                Origin.saveImage(full_name) ;
            }
            else if (colour == "5")
            {
                // To get the orange colour
                frame(Origin,255,100,0) ;
                Origin.saveImage(full_name) ;
            }
            else if (colour == "6")
            {
                // To get the purple colour
                frame(Origin,100,0,150) ;
                Origin.saveImage(full_name) ;
            }
        }
        else if (filter == "4")
        {
            Image rslt = Blur(Origin) ;
            rslt.saveImage(full_name) ;
        }
        cout << "Image has been saved successfully\n" ;
        cout << "\n====================\n" ;
        
    }
    else if (stoi(filter) >= 5 && stoi(filter) <=8)
    {
        switch (stoi(filter))
        {
          case 5:
            ResultBlackAndWhite();
            break;
          case 6:
            ResultFlip();
            break;
          case 7:
            ResultCrop();
            break;
          case 8:
            ResultResize();
        }
    }
    string cont ;
    cout << "Continue ?\n" ;
    cout << "1: Continue        2: Exit\n" ;
    cin >> cont ;
    while (cont != "1" && cont != "2")
        {
            cout << "Invalid choice ,please try again : \n" ;
            cin >> cont ;
        }
    if (cont == "1")
    {
        cout << "\n====================\n" ;
        main() ;
    }
    else 
    {
        cout << "Thanks for using the program ,good bye !" ;
        return 0;
    }
}