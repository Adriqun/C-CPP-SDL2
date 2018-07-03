#!/usr/bin/python

import pygame
import pyaudio

from core import Core
from wall import Wall
from map import Map


class Engine:

#-------------------------------------------------------------------------------------------------------

	def __init__( self ):

		self.core = Core( 60, 1024, 768, "Ninja" )

		self.wall = Wall()
		self.map = Map()
	
#-------------------------------------------------------------------------------------------------------

	def load( self ):

		self.core.setState( 0 )
		self.wall.load()
		self.map.load()

#-------------------------------------------------------------------------------------------------------	

	def handle( self ):
		for event in pygame.event.get():

			if event.type == pygame.QUIT:
				self.core.setQuit()

			self.map.handle( event )

#-------------------------------------------------------------------------------------------------------

	def states( self ):


		if self.core.getState() == 0:

			self.wall.fadein( 5 )
			self.map.fadein( 5 )
			
			self.wall.draw( self.core.getWindow() )
			self.map.draw( self.core.getWindow() )



#-------------------------------------------------------------------------------------------------------


	def loop( self ):
		while not self.core.isQuit():
			self.handle()
			self.core.fillDisplay()
			self.states()
			self.core.tickClock()
			pygame.display.update()
			
	def quit( self ):
		pygame.quit()
		






