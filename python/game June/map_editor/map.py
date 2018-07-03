#!/usr/bin/python

import pygame
from texture import Texture

class Map:

#-------------------------------------------------------------------------------------------------------
	
	def __init__( self ):
		self.texture = []
		self.x = []
		self.y = []

		self.nr = 14
		for i in range( 0, self.nr ):
			self.texture.append( Texture( "wall/" + str(i) + ".png" ) )
			self.x.append( [] )
			self.y.append( [] )

		self.type = 0
		self.txtnr = 0

		self.newtype = 0
		self.newtxtnr = 0

#-------------------------------------------------------------------------------------------------------

	def load( self, txt = 0 ):
		
		del self.x
		del self.y
		self.x = []
		self.y = []
		for i in range( 0, self.nr ):
			self.x.append( [] )
			self.y.append( [] )

		self.fo = open( "wall/" + str( txt ) + ".txt", "r" )

		self.t = 0
		self.x_t = 0
		self.y_t = 0
		self.line_t = ""
		
		for line in self.fo:	#File

			for i in range (0, len(line) ):	#Type
				if line[ i ] == '.':
					self.t = int( self.line_t )
					self.line_t = ""

					for j in range (i+1, len(line) ):	#Pos x
						if line[ j ] == '.':
							self.x_t = int( self.line_t )
							self.line_t = ""

							for k in range (j+1, len(line) ):	#Pos y
								if line[ k ] == '.':
									self.y_t = int( self.line_t )
									self.line_t = ""

									break
								self.line_t += line[ k ]
							break
						self.line_t += line[ j ]
					break
				self.line_t += line[ i ]

			# print self.t, self.x_t, self.y_t
			self.x[ self.t ].append( self.x_t )
			self.y[ self.t ].append( self.y_t )

		self.fo.close()
		del self.fo

		del self.t
		del self.x_t
		del self.y_t
		del self.line_t

#-------------------------------------------------------------------------------------------------------

	def handle( self, event ):

		self.mouseX, self.mouseY = pygame.mouse.get_pos()	#Get mouse pos
		self.range = 1280
		self.iterator = 0

		while self.iterator <= self.range:
			if self.mouseX < self.iterator:
				self.mouseX = self.iterator-128
				break
			self.iterator += 128
		self.iterator = 0
		while self.iterator <= self.range:
			if self.mouseY < self.iterator:
				self.mouseY = self.iterator-128
				break
			self.iterator += 128
			

		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_w:
				self.type += 1
				if self.type >= self.nr:
					self.type = 0
			elif event.key == pygame.K_s:
				self.type -= 1
				if self.type <= 0:
					self.type = self.nr-1
			
			elif event.key == pygame.K_d:
				self.txtnr += 1
				if self.txtnr >= 4:
					self.txtnr = 0
			elif event.key == pygame.K_a:
				self.txtnr -= 1
				if self.txtnr <= 0:
					self.txtnr = 3
		

		elif event.type == pygame.MOUSEBUTTONDOWN:
			print self.mouseX
			print self.mouseY
			self.fo = open( "wall/" + str( self.txtnr ) + ".txt", "a" )
			self.fo.write( str( self.type ) + '.' + str( self.mouseX ) + '.' + str( self.mouseY ) + ".\n" )
			self.fo.close()
			self.load( self.txtnr )
		

#-------------------------------------------------------------------------------------------------------
	
	def draw( self, window ):
		for i in range( 0, self.nr ):
			for j in range( 0, len( self.x[ i ] ) ):
				self.texture[ i ].setX( self.x[ i ][ j ] )
				self.texture[ i ].setY( self.y[ i ][ j ] )
				self.texture[ i ].draw( window )

		self.texture[ self.type ].setX( self.mouseX )
		self.texture[ self.type ].setY( self.mouseY )
		self.texture[ self.type ].draw( window )
		

#-------------------------------------------------------------------------------------------------------

	def getAlpha( self ):
		return self.texture[ 6 ].getAlpha()

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):
		for k in range( 0, self.nr ):
			self.texture[ k ].fadein( i, m )

#-------------------------------------------------------------------------------------------------------

	def fadeout( self, i = 1, m = 0 ):
		for k in range( 0, self.nr ):
			self.texture[ k ].fadeout( i, m )

#-------------------------------------------------------------------------------------------------------
