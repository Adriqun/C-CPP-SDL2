#!/usr/bin/python

import pygame
from texture import Texture
from font import Font

class Menuposition:
	
	def __init__( self, path ):
		self.texture = Texture( path, 4 )
		self.window = Texture( "menu/window.png" )
		self.click = pygame.mixer.Sound( "menu/click.wav" )
		self.on = 0	#SOUND
		self.type = 0	#WINDOW
		self.font = Font( "menu/KGHAPPY.ttf", 30 )
	
	def load( self, x, width, titlebot, bot ):
		self.texture.setX( x )
		self.texture.setY( bot +10 )
		
		self.window.setX( width/2 - self.window.getWidth()/2 )
		self.window.setY( titlebot -20 )
		#print self.texture.getLeft(), "  ", self.texture.getTop()
		self.font.createText( "SCORES", 0xd5, 0xad, 0x51 )
		self.font.setX( self.window.getLeft() + self.window.getWidth()/2 - self.font.getWidth()/2 )
		self.font.setY( self.window.getTop() +50 )

	
	def draw( self, screen ):
		if self.type == 1:
			self.window.draw( screen )
			self.font.draw( screen )
		else:
			self.texture.draw( screen )

	def fade( self, vel = 1 ):
		self.texture.fade( vel )
		self.window.fade( vel )
		self.font.fade( vel )	#And so on
		


	def getType( self ):
		return self.type

	def getRight( self ):
		return self.texture.getRight()



	def setState( self ):
		if self.on == 0:
			self.on = 1
		else:
			self.on = 0


	def handle( self, event ):
			
		self.focus = False
		if event.type == pygame.MOUSEBUTTONDOWN:
			self.focus = True
		
		if self.type == 0:
			self.texture.setOffset( 0 )
			self.x, self.y = pygame.mouse.get_pos()
			if self.x > self.texture.getLeft() and self.x < self.texture.getRight() and self.texture.getAlpha() > 250:
				if self.y > self.texture.getTop() and self.y < self.texture.getBot():
					if self.focus == True:
						if self.on == 0:
							self.click.play()
						self.texture.setOffset( 2 )
						if self.type == 0:
							self.type = 1
					else:
						self.texture.setOffset( 1 )

		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE or event.key == pygame.K_SPACE:
				if self.type == 1:
					if self.on == 0:
						self.click.play()
					self.type = 0



		
