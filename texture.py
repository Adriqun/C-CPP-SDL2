#!/usr/bin/python

import pygame

class Texture:
	
	def __init__( self, path, nr = 0 ):
		self.nr = nr
		
		if nr < 2:
			self.texture = pygame.image.load( path ).convert_alpha()
			self.rect = self.texture.get_rect()
		elif nr > 1:
			self.temporary = pygame.image.load( path ).convert_alpha()
			self.rect = self.temporary.get_rect()

			self.w = self.rect.width /nr
			self.h = self.rect.height
			self.texture = []

			for i in range( 0, nr-1 ):
				# print "Nr: ", i, " x=", self.w*i, " y=0, w=", self.w, " h=", self.h
				self.texture.append( self.temporary.subsurface( [self.w*i, 0, self.w, self.h] ) )

			del self.temporary

	def getWidth( self ):
		if self.nr < 2:
			return self.rect.width
		elif self.nr > 1:
			return self.rect.width / self.nr
		else:
			return 0

	def getHeight( self ):
		if self.nr < 2:
			return self.rect.height
		elif self.nr > 1:
			return self.rect.height / self.nr
		else:
			return 0
	
	def getLeft( self ):
		return self.rect.left()

	def getRight( self ):
		if self.nr < 2:
			return self.rect.right
		elif self.nr > 1:
			return self.rect.right / self.nr
		else:
			return 0

	def getBot( self ):
		return self.rect.bot

	def getTop( self ):
		return self.rect.top

	def draw( self, screen, offset = 0 ):
		
		if self.nr < 2:
			screen.blit( self.texture, ( self.rect.x, self.rect.y ) )
		elif self.nr > 1:
			screen.blit( self.texture[ offset ], ( self.rect.x, self.rect.y ) )



