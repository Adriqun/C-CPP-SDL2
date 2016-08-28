#!/usr/bin/python

import pygame
from texture import Texture
from text import Text

class Intro:

	'''
	nie jest to wersja finalowa aplikacji
	gra moze byc rozwijana rowniez dzieki tobie
	kod dziala na azsadzie open source
	aplikacja prezentuje wykorzystanie biblioteki pygame
	'''

#-------------------------------------------------------------------------------------------------------
	
	def __init__( self ):

		self.counter = 0
		self.quit = False

		#Textures
		self.preview = Text( "intro/Jaapokki-Regular.otf", 37 )
		self.shuriken = Texture( "intro/shuriken.png" )
		self.title = Text( "intro/Jaapokki-Regular.otf", 37 )
		self.author = Text( "intro/Jaapokki-Regular.otf", 37 )
		self.produced = Text( "intro/Jaapokki-Regular.otf", 37 )

		self.text_one = Text( "intro/Jaapokki-Regular.otf", 37 )
		self.text_two = Text( "intro/Jaapokki-Regular.otf", 37 )
		self.text_three = Text( "intro/Jaapokki-Regular.otf", 37 )
		self.text_four = Text( "intro/Jaapokki-Regular.otf", 37 )

#-------------------------------------------------------------------------------------------------------
	
	def load( self, width, height ):

		self.preview.createText( "When nothing makes sense...", [ 0xFF, 0xFF, 0xFF ] )
		self.preview.setX( width/2 - self.preview.getWidth()/2 )
		self.preview.setY( height/2 - self.preview.getHeight()/2 )

		self.title.createText( "Ninja", [ 0x70, 0xB7, 0x59 ] )
		self.title.setX( width/2 - self.title.getWidth()/2 - self.shuriken.getWidth() -10 )
		self.title.setY( height/2 - self.title.getHeight()/2 )
		
		
		self.shuriken.setX( self.title.getRight() +10 )
		self.shuriken.setY( height/2 - self.shuriken.getHeight()/2 )
		
		self.author.createText( "Adrian Michalek", [ 0xFF, 0xFF, 0xFF ] )
		self.author.setX( width/2 - self.author.getWidth()/2 )
		self.author.setY( height/2 - self.author.getHeight()/2 )

		self.produced.createText( "produced by", [ 0x70, 0xB7, 0x59 ] )
		self.produced.setX( width/2 - self.produced.getWidth()/2 )
		self.produced.setY( height/2 - self.produced.getHeight()/2 - self.author.getHeight() -10 )

		
		self.text_one.createText( "It's not a final version.", [ 0xFF, 0xFF, 0xFF ] )
		self.text_one.setX( width/2 - self.text_one.getWidth()/2 )
		self.text_one.setY( height/2 - self.text_one.getHeight()-20 )

		self.text_two.createText( "You can develop game by your own.", [ 0xFF, 0xFF, 0xFF ] )
		self.text_two.setX( width/2 - self.text_two.getWidth()/2 )
		self.text_two.setY( height/2 - self.text_two.getHeight()/2-10 )

		self.text_three.createText( "It's a open source code build with pygame library.", [ 0xFF, 0xFF, 0xFF ] )
		self.text_three.setX( width/2 - self.text_three.getWidth()/2 )
		self.text_three.setY( height/2 )

		self.text_four.createText( "Have a nice time!", [ 0x70, 0xB7, 0x59 ] )
		self.text_four.setX( width/2 - self.text_four.getWidth()/2 )
		self.text_four.setY( height/2 + self.text_four.getHeight()/2 +10 )

#-------------------------------------------------------------------------------------------------------

	def free( self ):
		#DELETE ALL
		del self.counter
		del self.quit
		
		self.preview.free()
		del self.preview

		self.shuriken.free()
		del self.shuriken
		
		self.title.free()
		del self.title
		
		self.author.free()
		del self.author

		self.produced.free()
		del self.produced
		
		self.text_one.free()
		del self.text_one

		self.text_two.free()
		del self.text_two

		self.text_three.free()
		del self.text_three

		self.text_four.free()
		del self.text_four

#-------------------------------------------------------------------------------------------------------
	
	def draw( self, screen ):
		
		self.preview.fadein( 3 )
		if self.preview.getAlpha() < 255:
			self.preview.draw( screen )
		else:
			self.title.fadein( 3 )
			self.shuriken.fadein( 3 )
	
		if self.title.getAlpha() < 255:
			self.title.draw( screen )
			self.shuriken.draw( screen )
		else:
			self.author.fadein( 3 )
			self.produced.fadein( 3 )

		if self.author.getAlpha() < 255:
			self.author.draw( screen )
			self.produced.draw( screen )
		else:
			self.counter += 1
			self.text_one.fadein( 3 )
			self.text_two.fadein( 3 )
			self.text_three.fadein( 3 )
			self.text_four.fadein( 3 )
		if self.counter < 500:
			self.text_one.draw( screen )
			self.text_two.draw( screen )
			self.text_three.draw( screen )
			self.text_four.draw( screen )
		else:
			self.quit = True

#-------------------------------------------------------------------------------------------------------

	def getQuit( self ):
		return self.quit

#-------------------------------------------------------------------------------------------------------
