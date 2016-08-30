##Linux

**install**<br/>
```
sudo apt-get install gobjc
```

**compile**<br/>
```
gcc hello.m `gnustep-config --objc-flags` `gnustep-config --base-libs` -o hello
```

**example**<br/>
```objective-c
import <Foundation/Foundation.h>

int main()
{
   /* my first program in Objective-C */
   NSLog(@"Hello, World! \n");
   
   return 0;
}
```

Help:<br/>
[askubuntu](http://askubuntu.com/questions/328343/how-to-compile-build-and-run-objective-c-program-in-ubuntu-using-terminal "ask ubuntu")<br/>
[ubuntuforum](https://ubuntuforums.org/showthread.php?t=1064045 "ubuntu forum")<br/>

