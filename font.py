#!/usr/bin/python

import pygame

class Font:
	
	def __init__( self, path, size = 1 ):
		self.font = pygame.font.Font( path, size )
		self.x = 0
		self.y = 0
		self.w = 0
		self.h = 0
		
	def createText( self, text, r = 0xFF, g = 0xFF, b = 0xFF ):
		self.texture = self.font.render( text, 1, (r, g, b) )
		self.w = self.texture.get_rect().width
		self.h = self.texture.get_rect().height
	
	def getWidth( self ):
		return self.w
	def getHeight( self ):
		return self.h

	
	def getLeft( self ):
		return self.x
	def getRight( self ):
		return self.x + self.w

	def getBot( self ):
		return self.y + self.h
	def getTop( self ):
		return self.y

	def setX( self, newx ):
		self.x = newx
	def setY( self, newy ):
		self.y = newy

	def draw( self, screen ):
		screen.blit( self.texture, ( self.x, self.y ) )



