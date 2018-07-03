#!/usr/bin/python

import pygame
from sprite import Sprite
from texture import Texture
from text import Text

class Menu_author_log:

#-------------------------------------------------------------------------------------------------------

	def __init__( self ):

		self.sprite = Sprite( "menu/author.png", 4 )
		self.window = Texture( "menu/window.png" )
		self.click = pygame.mixer.Sound( "menu/click.wav" )

		self.on = 0
		self.type = 0
		self.text = Text( "menu/KGHAPPY.ttf", 30 )

#-------------------------------------------------------------------------------------------------------
	
	def load( self, x, width, titlebot, bot ):

		self.sprite.setX( x )
		self.sprite.setY( bot +10 )

		self.window.setX( width/2 - self.window.getWidth()/2 )
		self.window.setY( titlebot -20 )
		

		self.text.createText( "AUTHOR", [ 0xd5, 0xad, 0x51 ] )
		self.text.setX( self.window.getLeft() + self.window.getWidth()/2 - self.text.getWidth()/2 )
		self.text.setY( self.window.getTop() +50 )

#-------------------------------------------------------------------------------------------------------

	def draw( self, screen ):
		if self.type == 1:
			self.window.draw( screen )
			self.text.draw( screen )
		else:
			self.sprite.draw( screen )

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):
		self.sprite.fadein( i, m )
		self.window.fadein( i, m )
		self.text.fadein( i, m )
#-------------------------------------------------------------------------------------------------------

	def fadeout( self, i = 1, m = 0 ):
		self.sprite.fadeout( i, m )
		self.window.fadeout( i, m )
		self.text.fadeout( i, m )

#-------------------------------------------------------------------------------------------------------

	def getState( self ):
		return self.type

#-------------------------------------------------------------------------------------------------------

	def getRight( self ):
		return self.sprite.getRight()

#-------------------------------------------------------------------------------------------------------

	def setState( self ):
		if self.on == 0:
			self.on = 1
		else:
			self.on = 0

#-------------------------------------------------------------------------------------------------------

	def handle( self, event ):
			
		self.focus = False
		if event.type == pygame.MOUSEBUTTONDOWN:
			self.focus = True
		
		if self.type == 0:
			self.sprite.setOffset( 0 )
			self.x, self.y = pygame.mouse.get_pos()
			if self.x > self.sprite.getLeft() and self.x < self.sprite.getRight() and self.sprite.getAlpha() == 255:
				if self.y > self.sprite.getTop() and self.y < self.sprite.getBot():
					if self.focus == True:
						if self.on == 0:
							self.click.play()
						self.sprite.setOffset( 2 )
						if self.type == 0:
							self.type = 1
					else:
						self.sprite.setOffset( 1 )
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE or event.key == pygame.K_SPACE:
				if self.type == 1:
					if self.on == 0:
						self.click.play()
					self.type = 0

#-------------------------------------------------------------------------------------------------------
