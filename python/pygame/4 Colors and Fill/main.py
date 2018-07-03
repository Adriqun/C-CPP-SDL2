#!/usr/bin/python

import pygame

pygame.init()

white = (0xFF, 0xFF, 0xFF)
black = (0, 0, 0)

gameDisplay = pygame.display.set_mode((800, 600))
pygame.display.set_caption('Slither')

quit = False;

while not quit:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			quit = True
		#print(event)

	gameDisplay.fill(white)
	pygame.display.update()

pygame.quit()
