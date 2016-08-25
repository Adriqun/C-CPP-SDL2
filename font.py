#!/usr/bin/python

import pygame

class Font:
	
	def __init__( self, path, size = 1, alpha = 1 ):

		self.font = pygame.font.Font( path, size )
		self.x = 0
		self.y = 0
		self.alpha = alpha
		
	def createText( self, text, r = 0xFF, g = 0xFF, b = 0xFF, alpha = 1 ):
		self.texture = self.font.render( text, 1, (r, g, b) )
		self.original = self.texture.copy()
		
		self.texture = self.original.copy()						#Copy original and
		self.texture.fill( (255, 255, 255, alpha), None, pygame.BLEND_RGBA_MULT )	#set start alpha
		
		self.w = self.texture.get_rect().width	#Set width
		self.h = self.texture.get_rect().height	#Set height
	
	def fade( self, vel = 1 ):
		if self.alpha < 255-vel and self.alpha > 0:
			self.alpha += vel
			self.texture = self.original.copy()
			self.texture.fill( (255, 255, 255, self.alpha), None, pygame.BLEND_RGBA_MULT )
	
	def getAlpha( self ):
		return self.alpha
	def draw( self, screen ):
		screen.blit( self.texture, ( self.x, self.y ) )
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



