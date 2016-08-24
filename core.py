#!/usr/bin/python

import pygame

class Core:

	def __init__( self, FPS, width, height, caption ):
		
		self.state = 0
		self.quit = False	#Main bool.
		self.FPS = FPS		#Frames per second.

		self.width = width	#Screen width
		self.height = height	#Screen height
		
		pygame.init()				#INIT PYGAME
		self.clock = pygame.time.Clock()	#Timer

		self.window = pygame.display.set_mode( ( width, height ) )	#Window
		pygame.display.set_caption( caption )				#Caption
		

	def getW( self ):
		return self.width

	def getH( self ):
		return self.height

	def getFPS( self ):
		return self.FPS

	def isQuit( self ):
		return self.quit

	def setQuit( self ):
		self.quit = True

	def fillDisplay( self ):
		self.window.fill( [ 0xFF, 0xFF, 0xFF ] )

	def tickClock( self ):
		self.clock.tick( self.FPS )

	def getWindow( self ):
		return self.window

	def getState( self ):
		return self.state

	def setState( self, newstate ):
		self.state = newstate
