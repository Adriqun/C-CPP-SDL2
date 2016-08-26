#!/usr/bin/python

import pygame
import webbrowser
from texture import Texture

class Menumus:
	
	def __init__( self, path, on = 0 ):
		self.texture = Texture( path, 4 )
		self.scratch = Texture( "menu/scratch.png" )
		self.click = pygame.mixer.Sound( "menu/click.wav" )
		self.type = 0
		self.state = 0
		self.on = on
		self.mouseup = 0

	
	def load( self, y ):
		self.texture.setX( 10 )
		self.texture.setY( y )
		
		self.scratch.setX( 10 )
		self.scratch.setY( y )

	def getBot( self ):
		return self.texture.getBot()
	
	def draw( self, screen ):
		self.texture.draw( screen )
		if self.type == 1:
			self.scratch.draw( screen )

	def fade( self, vel = 1, minA = 0, maxA = 255 ):
		self.texture.fade( vel, minA, maxA )
		self.scratch.fade( vel, minA, maxA )


	def getState( self ):
		if self.state != self.type:
			self.state = self.type
			#print "true!"
			return True
		return False



	def setState( self ):
		if self.on == 0:
			self.on = 1
		else:
			self.on = 0
		# print self.on


	def handle( self, event ):
			
		self.focus = False
		self.texture.setOffset( 0 )

		if event.type == pygame.MOUSEBUTTONDOWN:
			self.focus = True
			self.mouseup = 1
		elif event.type == pygame.MOUSEBUTTONUP:
			self.mouseup = 0
		
		
		self.x, self.y = pygame.mouse.get_pos()
		if self.x > self.texture.getLeft() and self.x < self.texture.getRight() and self.texture.getAlpha() > 250:
			if self.y > self.texture.getTop() and self.y < self.texture.getBot():
				if self.focus == True:
					if self.on == 0:
						self.click.play()
					if self.type == 0:
						self.type = 1
					else:
						self.type = 0
				if self.focus == True or self.mouseup == 1:
					self.texture.setOffset( 2 )
				else:
					self.texture.setOffset( 1 )



		
