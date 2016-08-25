#!/usr/bin/python

import pygame

class Texture:
	
	def __init__( self, path, nr = 0, alpha = 1 ):

		self.offset = 0		#Offset counter
		self.nr = nr		#Set how many offset's
		self.x = 0		#Set x
		self.y = 0		#Set y
		self.alpha = alpha	#Set alpha
		
		if nr < 2:	#If we don't have offset's
			self.texture = pygame.image.load( path ).convert_alpha()	#Load texture
			self.original = self.texture.copy()				#Set Original texture
			self.w = self.texture.get_rect().width				#Set width of texture
			self.h = self.texture.get_rect().height				#Set height of texture

			self.texture = self.original.copy()						#Copy original and
			self.texture.fill( (255, 255, 255, alpha), None, pygame.BLEND_RGBA_MULT )	#set start alpha

		elif nr > 1:	#Else
			self.temporary = pygame.image.load( path ).convert_alpha()	#Load temporary texture
			self.original = []						#Create space for original texture
			self.w = self.temporary.get_rect().width /nr			#Set width of texture / number of offset's
			self.h = self.temporary.get_rect().height				#Set height of texture
			self.texture = []						#Create space for texture
			
			for i in range( 0, self.nr ):
				# print "Nr: ", i, " x=", self.w*i, " y=0, w=", self.w, " h=", self.h
				self.texture.append( self.temporary.subsurface( [self.w*i, 0, self.w, self.h] ) )
				self.original.append( self.texture[ i ].copy() )

				self.texture[ i ] = self.original[ i ].copy()						#Copy original and
				self.texture[ i ].fill( (255, 255, 255, self.alpha), None, pygame.BLEND_RGBA_MULT )	#set start alpha
			del self.temporary	#Delete old texture
	
	def setOffset( self, offset ):
		self.offset = offset


	'''
	def setAlpha( self, alpha ):
		if self.nr < 2:
			self.texture.fill( (255, 255, 255, alpha), None, pygame.BLEND_RGBA_MULT )
		elif self.nr > 1:
			for i in range( 0, self.nr ):
				self.texture[ i ].fill( (255, 255, 255, alpha), None, pygame.BLEND_RGBA_MULT )
	'''

	def fade( self, vel = 1 ):
		if self.alpha < 255-vel and self.alpha > 0:
			self.alpha += vel

			if self.nr < 2:
				self.texture = self.original.copy()
				self.texture.fill( (255, 255, 255, self.alpha), None, pygame.BLEND_RGBA_MULT )
			elif self.nr > 1:
				for i in range( 0, self.nr ):
					self.texture[ i ] = self.original[ i ].copy()
					self.texture[ i ].fill( (255, 255, 255, self.alpha), None, pygame.BLEND_RGBA_MULT )
		
		
		
	def draw( self, screen ):
		if self.nr < 2:
			screen.blit( self.texture, ( self.x, self.y ) )
		elif self.nr > 1:
			screen.blit( self.texture[ self.offset ], ( self.x, self.y ) )
	def getAlpha( self ):
		return self.alpha
	def setX( self, newx ):
		self.x = newx
	def setY( self, newy ):
		self.y = newy
	def getHeight( self ):
		return self.h
	def getWidth( self ):
		return self.w
	def getLeft( self ):
		return self.x
	def getRight( self ):
		return self.x + self.w
	def getBot( self ):
		return self.y + self.h
	def getTop( self ):
		return self.y
