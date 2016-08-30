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
