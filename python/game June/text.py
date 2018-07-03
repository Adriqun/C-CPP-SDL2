#!/usr/bin/python

import pygame

class Text:

#-------------------------------------------------------------------------------------------------------

	def __init__( self, path, size, alpha = 0 ):

		self.alpha = alpha				#Set start alpha
		self.font = pygame.font.Font( path, size )	#Load font
		self.x = 0	#Set x
		self.y = 0	#Set y

#-------------------------------------------------------------------------------------------------------

	def free( self ):
		del self.alpha
		del self.x
		del self.y
		del self.w
		del self.h
		del self.texture
		del self.original

#-------------------------------------------------------------------------------------------------------

	def createText( self, text, color ):

		#Load texture
		try:
			self.texture = self.font.render( text, 1, color )
		except pygame.error, message:
			print "Cannot create text: ", text
			raise SystemExit, message
		self.texture.convert_alpha()

		#Set original texture
		self.original = self.texture.copy()

		#Set start alpha
		self.texture.fill( ( 255, 255, 255, self.alpha ), None, pygame.BLEND_RGBA_MULT )
		
		self.w = self.texture.get_rect().width
		self.h = self.texture.get_rect().height
		
		#Delete font
		del self.font

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):

		if self.alpha < m:

			self.alpha += i

			if self.alpha > m:
				self.alpha = m
			
			self.texture = self.original.copy()
			self.texture.fill( ( 255, 255, 255, self.alpha ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------
		
	def fadeout( self, i = 1, m = 0 ):

		if self.alpha > m:

			self.alpha -= i

			if self.alpha < m:
				self.alpha = m
			
			self.texture = self.original.copy()
			self.texture.fill( ( 255, 255, 255, self.alpha ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------

	def draw( self, window ):
		window.blit( self.texture, ( self.x, self.y ) )

#-------------------------------------------------------------------------------------------------------


	def getAlpha( self ):
		return self.alpha

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
