#!/usr/bin/python

import pygame

class Texture:

#-------------------------------------------------------------------------------------------------------

	def __init__( self, path, alpha = 0 ):

		self.x = 0		#Set x
		self.y = 0		#Set y

		self.r = 0xFF	#Red
		self.g = 0xFF	#Green
		self.b = 0xFF	#Blue
		self.a = alpha	#Set alpha
		
		#Load texture
		try:
			self.texture = pygame.image.load( path )
		except pygame.error, message:
			print "Cannot load image: ", path
			raise SystemExit, message
		self.texture.convert_alpha()
			
		#Set original texture
		self.original = self.texture.copy()

		self.w = self.texture.get_rect().width
		self.h = self.texture.get_rect().height
			
		#Set start alpha
		self.texture.fill( ( self.r, self.g, self.b, self.a ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------

	def free( self ):

		del self.w
		del self.h
		del self.x
		del self.y

		del self.texture
		del self.original

		del self.r
		del self.g
		del self.b
		del self.a

#-------------------------------------------------------------------------------------------------------

	def setColor( self, r, g, b ):
		if self.r != r or self.g != g or self.b != b:

			self.r = r
			self.g = g
			self.b = b

			self.texture = self.original.copy()
			self.texture.fill( ( self.r, self.g, self.b, self.a ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):

		if self.a < m:

			self.a += i

			if self.a > m:
				self.a = m
			
			self.texture = self.original.copy()
			self.texture.fill( ( self.r, self.g, self.b, self.a ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------
		
	def fadeout( self, i = 1, m = 0 ):

		if self.a > m:

			self.a -= i

			if self.a < m:
				self.a = m

			self.texture = self.original.copy()
			self.texture.fill( ( self.r, self.g, self.b, self.a ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------

	def draw( self, window ):
		window.blit( self.texture, ( self.x, self.y ) )

#-------------------------------------------------------------------------------------------------------

	def setAlpha( self, alpha = 0xFF ):
		if self.a != alpha:

			self.a = alpha
			self.texture = self.original.copy()
			self.texture.fill( ( self.r, self.g, self.b, self.a ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------

	def getAlpha( self ):
		return self.a

#-------------------------------------------------------------------------------------------------------

	def setX( self, x ):
		self.x = x
	def setY( self, y ):
		self.y = y

#-------------------------------------------------------------------------------------------------------

	def getHeight( self ):
		return self.h
	def getWidth( self ):
		return self.w

#-------------------------------------------------------------------------------------------------------

	def getLeft( self ):
		return self.x
	def getRight( self ):
		return self.x + self.w
	
#-------------------------------------------------------------------------------------------------------

	def getTop( self ):
		return self.y
	def getBot( self ):
		return self.y + self.h

#-------------------------------------------------------------------------------------------------------

	def getX( self ):
		return self.x
	def getY( self ):
		return self.y

#-------------------------------------------------------------------------------------------------------
