#!/usr/bin/python

import pygame

class Sprite:

#-------------------------------------------------------------------------------------------------------

	def __init__( self, path, nr = 0, alpha = 0 ):

		self.x = 0		#Set x
		self.y = 0		#Set y
		self.nr = nr		#Set how many offset's
		self.offset = 0		#Offset

		self.r = 0xFF	#Red
		self.g = 0xFF	#Green
		self.b = 0xFF	#Blue
		self.a = alpha	#Set alpha

		if self.nr < 2:
			print "Number cannot be < 2 - class Sprite"
		else:
			try:
				self.temporary = pygame.image.load( path )
			except pygame.error, message:
				print "Cannot load image: ", path
				raise SystemExit, message
			self.temporary.convert_alpha()
			
			#Create space for textures
			self.texture = []
			self.original = []

			self.w = self.temporary.get_rect().width / self.nr	#Set w
			self.h = self.temporary.get_rect().height		#Set h
			
			for i in range( 0, self.nr ):

				#Set textures
				self.texture.append( self.temporary.subsurface( [ self.w*i, 0, self.w, self.h ] ) )
				self.original.append( self.texture[ i ].copy() )
				
				#Set start alpha
				self.texture[ i ].fill( ( 0xFF, 0xFF, 0xFF, 0xFF ), None, pygame.BLEND_RGBA_MULT )

			#Delete temporary texture
			del self.temporary

#-------------------------------------------------------------------------------------------------------

	def free( self ):

		del self.w
		del self.h
		del self.x
		del self.y

		for i in range( 0, self.nr ):
			del self.texture[ i ]
			del self.original[ i ]

		del self.nr
		del self.offset
		del self.r
		del self.g
		del self.b
		del self.a

#-------------------------------------------------------------------------------------------------------

	def setAlpha( self, alpha = 0xFF ):
		if self.a != alpha:

			self.a = alpha

			for i in range( 0, self.nr ):
				self.texture[ i ] = self.original[ i ].copy()
				self.texture[ i ].fill( ( self.r, self.g, self.b, self.a ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------

	def getAlpha( self ):
			return self.a

#-------------------------------------------------------------------------------------------------------

	def setColor( self, r, g, b ):
		if self.r != r or self.g != g or self.b != b:

			self.r = r
			self.g = g
			self.b = b

			for i in range( 0, self.nr ):
				self.texture[ i ] = self.original[ i ].copy()
				self.texture[ i ].fill( ( self.r, self.g, self.b, self.a ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------

	def draw( self, window ):
		window.blit( self.texture[ self.offset ], ( self.x, self.y ) )

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):

		if self.a < m:

			self.a += i

			if self.a > m:
				self.a = m
			
			for i in range( 0, self.nr ):
				self.texture[ i ] = self.original[ i ].copy()
				self.texture[ i ].fill( ( self.r, self.g, self.b, self.a ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------
		
	def fadeout( self, i = 1, m = 0 ):

		if self.a > m:

			self.a -= i

			if self.a < m:
				self.a = m
			
			for i in range( 0, self.nr ):
				self.texture[ i ] = self.original[ i ].copy()
				self.texture[ i ].fill( ( self.r, self.g, self.b, self.a ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------

	def setOffset( self, offset ):
		self.offset = offset

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
