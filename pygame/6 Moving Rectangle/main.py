#!/usr/bin/python

import pygame

pygame.init()

gameDisplay = pygame.display.set_mode((800, 600))
pygame.display.set_caption('Slither')

quit = False;

lead_x = 300
lead_y = 300
vel = 5;

while not quit:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			quit = True
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_LEFT:
				lead_x -= vel
			if event.key == pygame.K_RIGHT:
				lead_x += vel

	gameDisplay.fill([0xFF, 0xFF, 0xFF])
	
	pygame.draw.rect( gameDisplay, [0, 0, 0], [lead_x, lead_y, 10, 10])
	
	pygame.display.update()

pygame.quit()
