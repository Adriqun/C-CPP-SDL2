#!/usr/bin/python

import pygame

pygame.init()

gameDisplay = pygame.display.set_mode((800, 600))
pygame.display.set_caption('Slither')

quit = False;

lead_x = 300
lead_y = 300
vel = 1
lead_x_change = 0

clock = pygame.time.Clock()


while not quit:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			quit = True
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_LEFT:
				lead_x_change = -vel
			if event.key == pygame.K_RIGHT:
				lead_x_change = vel

		if event.type == pygame.KEYUP:
			if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
				lead_x_change = 0
				

	lead_x += lead_x_change

	gameDisplay.fill([0xFF, 0xFF, 0xFF])
	pygame.draw.rect( gameDisplay, [0, 0, 0], [lead_x, lead_y, 10, 10])

	clock.tick(120)

	pygame.display.update()

pygame.quit()
