#!/usr/bin/python

import pygame

class Texture:
	
	def __init__( self, path, nr = 0 ):
		self.offset = 0
		self.nr = nr
		self.x = 0
		self.y = 0
		self.w = 0
		self.h = 0
		
		if nr < 2:
			self.texture = pygame.image.load( path ).convert_alpha()
			self.w = self.texture.get_rect().width
			self.h = self.texture.get_rect().height
		elif nr > 1:
			self.temporary = pygame.image.load( path ).convert_alpha()
			self.w = self.temporary.get_rect().width /nr
			self.h = self.temporary.get_rect().height

			self.texture = []

			for i in range( 0, nr ):
				# print "Nr: ", i, " x=", self.w*i, " y=0, w=", self.w, " h=", self.h
				self.texture.append( self.temporary.subsurface( [self.w*i, 0, self.w, self.h] ) )

			del self.temporary
	
	def getHeight( self ):
		return self.h
	def getWidth( self ):
		return self.w
	
	def getLeft( self ):
		return self.x
	def getRight( self ):
		return self.x + self.w

	def getBot( self ):
		return 	self.y + self.h
	def getTop( self ):
		return self.y

	def setX( self, newx ):
		self.x = newx
		#print x

	def setY( self, newy ):
		self.y = newy
		#print y

	def setOffset( self, offset ):
		self.offset = offset
	
	'''
	def scale( self, w, h ):
		self.texture = pygame.transform.scale( self.texture, ( w, h ) )
	'''

	def draw( self, screen ):
		
		if self.nr < 2:
			screen.blit( self.texture, ( self.x, self.y ) )
		elif self.nr > 1:
			screen.blit( self.texture[ self.offset ], ( self.x, self.y ) )



