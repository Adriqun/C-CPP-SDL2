#!/bin/bash

#Define global
var="global_variable"

function func {

#Define local
local var="local_variable"

#Print
echo function: -----$var

}

echo result is ---------$var

#Call func function
func

echo result is ---------$var
