## Introduction
Console application based on **eleven** sorting algorithms :books:.                                                            

## How it works
You have to write **one** number between 1-45 000 000, don't worry about mistakes because application care about exceptions. If you wrote a
number you will see the time of each sorting algorithms.

Linux                                                                                                                      
![1](https://cloud.githubusercontent.com/assets/19840443/17803547/5bb7dcf2-65f7-11e6-873d-83ccdbdc0e33.png)
                                                                                                                          
Windows                                                                                                                 
![0](https://cloud.githubusercontent.com/assets/19840443/17805982/57e799cc-6602-11e6-89ac-94804a5d1556.png)

## Download
linux - https://docs.google.com/uc?authuser=0&id=0B36D1JHNNqr-M0wxQU1BWGlFMms&export=download <br/>
windows - https://docs.google.com/uc?authuser=0&id=0B36D1JHNNqr-bm0xNUc4aWVZWmc&export=download <br/>
to edit - https://docs.google.com/uc?authuser=0&id=0B36D1JHNNqr-U3BocDRDQVBvX2s&export=download <br/>
to edit on windows - https://docs.google.com/uc?authuser=0&id=0B36D1JHNNqr-MFNJbmpJVVdKYms&export=download <br/>

## In detail
**Align to center**                                                                                                       
1. You need to know console width.											     
2. In C add														
![2](https://cloud.githubusercontent.com/assets/19840443/17803957/b7f7c908-65f9-11e6-90ed-0ac55eee6a51.png)
                                                                                                                            
**Colors without windows.h**                                                                                              
1. We have to know the special code formatting.                                                                           
2. Code looks - "\x1B[" + _number_ + 'm'.                                                                                 
3. The list of formatting here http://misc.flogisoft.com/bash/tip_colors_and_formatting                                   
4. For example code in C below.                                                                                           
![3](https://cloud.githubusercontent.com/assets/19840443/17804073/44161566-65fa-11e6-8414-c11afa7e1c9a.png)
                                                                                                                          
**Sleep on linux**                                                                                                        
1. Add in C library - #include "unistd.h"                                                                                 
2. Call usleep(**microseconds**)                                                                                          
                                                                                                                          
**Cannot open executive file on linux**                                                                                   
1. Go by **cd** command to folder of application or open terminal inside of this folder.                                  
2. Call **chmod +x "ex_name"** then you need to write **./ex_name** - linux protect for security reasons.                 
                                                                                                                          
**How to clean console window - linux**                                                                                   
1. Call **reset** in C system("reset").                                                                                   
2. More quickly call **tput reset** in C system("tput reset").                                                            
