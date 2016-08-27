#!/usr/bin/python

import pygame

class Texture:

#-------------------------------------------------------------------------------------------------------

	def __init__( self, nr = 0, alpha = 0 ):
		
		self.alpha = alpha	#Set start alpha
		self.nr = nr		#Set how many offset's
		self.x = 0		#Set x
		self.y = 0		#Set y
		self.offset = 0		#Set offset		

#-------------------------------------------------------------------------------------------------------

	def load( self, path ):
		
		#If we don't have offset's
		if self.nr < 2:
			
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
			self.texture.fill( ( 255, 255, 255, self.alpha ), None, pygame.BLEND_RGBA_MULT )

		elif self.nr > 1:

			#Load temporary texture
			try:
				self.tex = pygame.image.load( path )
			except pygame.error, message:
				print "Cannot load image: ", path
				raise SystemExit, message
			self.tex.convert_alpha()
			
			#Create space for textures
			self.texture = []
			self.original = []

			self.w = self.tex.get_rect().width / self.nr
			self.h = self.tex.get_rect().height
			
			for i in range( 0, self.nr ):

				#Set textures
				self.texture.append( self.tex.subsurface( [ self.w*i, 0, self.w, self.h ] ) )
				self.original.append( self.texture[ i ].copy() )
				
				#Set start alpha
				self.texture[ i ].fill( ( 255, 255, 255, self.alpha ), None, pygame.BLEND_RGBA_MULT )

			#Delete temporary texture
			del self.tex

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):

		if self.alpha < m:

			self.alpha += i

			if self.alpha > m:
				self.alpha = m
			
			if self.nr < 2:
				self.texture = self.original.copy()
				self.texture.fill( ( 255, 255, 255, self.alpha ), None, pygame.BLEND_RGBA_MULT )
			elif self.nr > 1:
				for i in range( 0, self.nr ):
					self.texture[ i ] = self.original[ i ].copy()
					self.texture[ i ].fill( ( 255, 255, 255, self.alpha ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------
		
	def fadeout( self, i = 1, m = 0 ):

		if self.alpha > m:

			self.alpha -= i

			if self.alpha < m:
				self.alpha = m
			
			if self.nr < 2:
				self.texture = self.original.copy()
				self.texture.fill( ( 255, 255, 255, self.alpha ), None, pygame.BLEND_RGBA_MULT )
			elif self.nr > 1:
				for i in range( 0, self.nr ):
					self.texture[ i ] = self.original[ i ].copy()
					self.texture[ i ].fill( ( 255, 255, 255, self.alpha ), None, pygame.BLEND_RGBA_MULT )

#-------------------------------------------------------------------------------------------------------

	def draw( self, window ):

		if self.nr < 2:
			window.blit( self.texture, ( self.x, self.y ) )

		elif self.nr > 1:
			window.blit( self.texture[ self.offset ], ( self.x, self.y ) )

#-------------------------------------------------------------------------------------------------------

	def setOffset( self, offset ):
		self.offset = offset

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
