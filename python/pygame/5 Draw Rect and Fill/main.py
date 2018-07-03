#!/usr/bin/python

import pygame

pygame.init()

white = (0xFF, 0xFF, 0xFF)
black = (0, 0, 0)
red = (255, 0, 0)

gameDisplay = pygame.display.set_mode((800, 600))
pygame.display.set_caption('Slither')

quit = False;

while not quit:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			quit = True
		#print(event)

	gameDisplay.fill(white)
	#show graphic

	pygame.draw.rect(gameDisplay, black, [400, 300, 50, 100])
	pygame.draw.rect(gameDisplay, red, [400, 300, 50, 50])
	gameDisplay.fill(red, rect=[200, 200, 100, 100])

	#show graphic
	pygame.display.update()

pygame.quit()
