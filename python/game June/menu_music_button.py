#!/usr/bin/python

import pygame
from sprite import Sprite
from texture import Texture

class Menu_music_button:

#-------------------------------------------------------------------------------------------------------

	def __init__( self, path, on = 0 ):

		self.sprite = Sprite( path, 4 )

		self.scratch = Texture( "menu/scratch.png" )
		self.click = pygame.mixer.Sound( "menu/click.wav" )

		self.type = 0
		self.state = 0
		self.on = on
		self.mouseup = 0

#-------------------------------------------------------------------------------------------------------
	
	def load( self, y ):
		self.sprite.setX( 10 )
		self.sprite.setY( y )
		
		self.scratch.setX( 10 )
		self.scratch.setY( y )

#-------------------------------------------------------------------------------------------------------

	def getBot( self ):
		return self.sprite.getBot()

#-------------------------------------------------------------------------------------------------------
	
	def draw( self, window ):
		self.sprite.draw( window )
		if self.type == 1:
			self.scratch.draw( window )

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):
		self.sprite.fadein( i, m )
		self.scratch.fadein( i, m )

#-------------------------------------------------------------------------------------------------------

	def fadeout( self, i = 1, m = 0 ):
		self.sprite.fadeout( i, m )
		self.scratch.fadeout( i, m )

#-------------------------------------------------------------------------------------------------------

	def getState( self ):
		if self.state != self.type:
			self.state = self.type
			#print "true!"
			return True
		return False

#-------------------------------------------------------------------------------------------------------

	def setState( self ):
		if self.on == 0:
			self.on = 1
		else:
			self.on = 0
		# print self.on

#-------------------------------------------------------------------------------------------------------

	def handle( self, event ):
			
		self.focus = False
		self.sprite.setOffset( 0 )

		if event.type == pygame.MOUSEBUTTONDOWN:
			self.focus = True
			self.mouseup = 1
		elif event.type == pygame.MOUSEBUTTONUP:
			self.mouseup = 0
		
		
		self.x, self.y = pygame.mouse.get_pos()
		if self.x > self.sprite.getLeft() and self.x < self.sprite.getRight() and self.sprite.getAlpha() == 255:
			if self.y > self.sprite.getTop() and self.y < self.sprite.getBot():
				if self.focus == True:
					if self.on == 0:
						self.click.play()
					if self.type == 0:
						self.type = 1
					else:
						self.type = 0
				if self.focus == True or self.mouseup == 1:
					self.sprite.setOffset( 2 )
				else:
					self.sprite.setOffset( 1 )

#-------------------------------------------------------------------------------------------------------
