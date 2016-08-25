#!/usr/bin/python

import pygame
from texture import Texture
from font import Font

class Intro:
	
	def __init__( self ):
		self.counter = 0
		self.quit = False

		#Textures
		self.preview = Font( "intro/Jaapokki-Regular.otf", 37 )
		self.shuriken = Texture( "intro/shuriken.png" )
		self.title = Font( "intro/Jaapokki-Regular.otf", 37 )
		self.author = Font( "intro/Jaapokki-Regular.otf", 37 )
		self.produced = Font( "intro/Jaapokki-Regular.otf", 37 )

		self.frames = 3
	
	def load( self, width, height ):

		self.preview.createText( "When nothing makes sense...", 0xFF, 0xFF, 0xFF )
		self.preview.setX( width/2 - self.preview.getWidth()/2 )
		self.preview.setY( height/2 - self.preview.getHeight()/2 )

		self.title.createText( "Jump and jump", 0x70, 0xB7, 0x59 )
		self.title.setX( width/2 - self.title.getWidth()/2 - self.shuriken.getWidth() -10 )
		self.title.setY( height/2 - self.title.getHeight()/2 )

		self.shuriken.setX( self.title.getRight() +10 )
		self.shuriken.setY( height/2 - self.shuriken.getHeight()/2 )
		
		self.author.createText( "Adrian Michalek", 0xFF, 0xFF, 0xFF )
		self.author.setX( width/2 - self.author.getWidth()/2 )
		self.author.setY( height/2 - self.author.getHeight()/2 )

		self.produced.createText( "prudeced by", 0x70, 0xB7, 0x59 )
		self.produced.setX( width/2 - self.produced.getWidth()/2 )
		self.produced.setY( height/2 - self.produced.getHeight()/2 - self.author.getHeight() -10 )
		
	
	def draw( self, screen ):
		
		self.counter += 1

		self.preview.fade( 3 )
		if self.preview.getAlpha() < 250:
			self.preview.draw( screen )
		else:
			self.title.fade( 3 )
			self.shuriken.fade( 3 )
	
		if self.title.getAlpha() < 250:
			self.title.draw( screen )
			self.shuriken.draw( screen )
		else:
			self.author.fade( 3 )
			self.produced.fade( 3 )

		if self.author.getAlpha() < 250:
			self.author.draw( screen )
			self.produced.draw( screen )
		else:
			self.quit = True

	def getQuit( self ):
		return self.quit






























