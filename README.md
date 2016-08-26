##Introduction
Work in progress...
##Following changes

Free font - [KG HAPPY](http://www.fontspace.com/kimberly-geswein/kg-happy "KG HAPPY")<br />
Free gui - [FREE FANTASY GAME GUI](http://www.gameart2d.com/free-fantasy-game-gui.html "FREE FANTASY GAME GUI")<br /><br />
Menu takes a lot of time because you need to set all buttons, it's not a ready made something that you can click and set, you need to launch your application 100 times before final version.<br/><br/>
Below you see set buttons, each works.<br/>
To exit topical window for example menu to leave click [escape]. <br/>
Every texture created by class Texture have function called fade( val = 1 ), you can fadeout by fade() with negative number or fadein with positive.<br/><br/>
![menu](https://cloud.githubusercontent.com/assets/19840443/17998044/8f1e7b2a-6b72-11e6-965e-b39c9b23ee3c.png)<br/><br/>

I want that my champion can move right and left. We need to move also background. I introduce you my difficulty. We have **two** the same textures, when player moves right we subtract position x. We use **two** textures because when first background will be a little father we will have a white space beetwen two. Ok what if player moves left? We need to quickly set second texture on another position. <br/>

Move left.
![left](https://cloud.githubusercontent.com/assets/19840443/17999014/8c2611d0-6b77-11e6-94cb-253c8959e5c4.png)<br/>
Move right.
![right](https://cloud.githubusercontent.com/assets/19840443/17999030/9c306490-6b77-11e6-975e-e6c572f1e0b4.png)<br/>
<br/><br/>
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
