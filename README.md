##Introduction
Work in progress...
##Following changes

Free font - [KG HAPPY](http://www.fontspace.com/kimberly-geswein/kg-happy "KG HAPPY")<br />
Free gui - [FREE FANTASY GAME GUI](http://www.gameart2d.com/free-fantasy-game-gui.html "FREE FANTASY GAME GUI")<br /><br />
Menu takes a lot of time because you need to set all buttons, it's not a ready made something that you can click and set, you need to launch your application 100 times before final version.<br />
Ok Below you see my 3hour's work of setting the buttons, each works.<br />
To exit topical window for example menu to leave you have to click [escape] or [space]. <br />
**Full menu**<br />
![3](https://cloud.githubusercontent.com/assets/19840443/17930208/55a3ab18-6a05-11e6-8557-2d834d20f2fd.png)
<br />
**Author window** - Currently you don't see a text. <br/>
![4](https://cloud.githubusercontent.com/assets/19840443/17930261/9497fd92-6a05-11e6-94f6-b00e23266d0a.png)
**Scores** - Looks the same, but I will put a diffrent text.<br/>
![5](https://cloud.githubusercontent.com/assets/19840443/17930279/a2ca2124-6a05-11e6-8699-2ea39aac805b.png)

I add alpha functions. Now every texture created by class Texture have function called fade( val = 1 ), you can fadeOut by fade() with negative number and fadeIn with positive. I'm not sure about my English when I want to describe deep affairs, but I hope that you know what I mean. <br/>
The thing that you see below is a menu with changed light.<br/>
![6](https://cloud.githubusercontent.com/assets/19840443/17967374/1d059740-6ac7-11e6-9895-9472801c70f0.png)
That's why: ![alpha](https://cloud.githubusercontent.com/assets/19840443/17968017/bb6f0f30-6aca-11e6-81ad-77fa0964ee2d.png) <br/>
Texture of light is brighter than title, when I changed the velocity of showing alpha that result was worse. <br/>

Simple intro below (one of three frames from intro) <br/>
![7](https://cloud.githubusercontent.com/assets/19840443/17968114/58668bc4-6acb-11e6-8702-61a4d197d641.png)

I want that my champion can move right and left. We need to move also background. I show you my difficulty what I mean by this image. We have **two** the same textures, when player moves right we subtract position x. We use **two** textures because when first background will be a little father we will have a white space beetwen two. Ok what if player moves left? We need to quickly set second texture on another position. <br/>

Move left.
![c1](https://cloud.githubusercontent.com/assets/19840443/17997244/ad355322-6b6d-11e6-8c3e-7cfd341b4ff0.png)<br/>
Move right.
![c2](https://cloud.githubusercontent.com/assets/19840443/17997260/c6c7d3d2-6b6d-11e6-9443-9dc010a005bf.png)<br/>
It's simple, we render artificial moving.<br/><br/>

So, how it works while we are playing? <br/>
Draw function below: <br/>
```python
def draw( self, display, direction ):
		
		if direction == 1:	# Move left
			if self.bg_one.getX() == 0:
				self.bg_two.setX( -self.bg_two.getWidth() )
			elif self.bg_two.getX() == 0:
				self.bg_one.setX( -self.bg_one.getWidth() )

			self.bg_one.setX( self.bg_one.getX() + 1 )  # 1 - mean velocity, we can also add another variable
			self.bg_two.setX( self.bg_two.getX() + 1 )

		elif direction == 2: # Move right
			if self.bg_one.getX() == 0:
				self.bg_two.setX( self.bg_two.getWidth() )
			elif self.bg_two.getX() == 0:
				self.bg_one.setX( self.bg_one.getWidth() )
      
			self.bg_one.setX( self.bg_one.getX() - 1 )
			self.bg_two.setX( self.bg_two.getX() - 1 )

		# render
		self.bg_one.draw( display )
		self.bg_two.draw( display )
```

