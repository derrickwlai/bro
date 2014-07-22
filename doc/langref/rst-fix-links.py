#!/usr/bin/env python

# NOTE: this script fixes RST links that were incorrectly
#       generated from the process of converting a TEXINFO 
#       file into RST via HTML (TEXINFO => HTML => RST)
#
#       This script is meant to run from within the root
#       directory and it walks throught the tree to find
#       and fix all RST files

import os
import re

scriptName = __file__.split("/")[1]
tagsChanged = 0
linksChanged = 0

def fileFixLink(fileName, oldString, newString):
  global linksChanged
  s = open(fileName).read()
  if oldString in s:
    print "\nFIXING A LINK:"
    print "==============="
    print "oldString: " + oldString
    print "newString: " + newString
    print "file: " + fileName
    linksChanged = linksChanged + 1
    s = s.replace(oldString, newString)
    f = open(fileName, 'w')
    f.write(s)
    f.flush()
    f.close()

def fileAddTag(fileName, text, tag):
  global tagsChanged
  regexp = re.compile(r'(.)\1{5,}')
  newTag = ".. _" + tag + ":\n"
  s = open(fileName).read() 
  # If tag already present, skip it
  if newTag in s:
    return
  linesUpdated = []
  lines = s.split("\n")
  numLines = len(lines)
  index = 0
  # Badly written, eliminate repetitive code
  while index < numLines:
    if index == numLines - 1:  # last line
      linesUpdated.append(lines[index])
      index = index + 1
      continue
    if text == lines[index] and regexp.search(lines[index+1]) is not None:
      print "\nINSERTING A TAG" 
      print "================"
      print "text: " + text
      print "newTag: " + newTag
      print "first line: " + lines[index]
      print "second line: " + lines[index+1]
      print "file: " + fileName
      tagsChanged = tagsChanged + 1
      linesUpdated.append(newTag)
      linesUpdated.append(lines[index])  
      index = index + 1
      continue
    linesUpdated.append(lines[index]) 
    index = index + 1

  f = open(fileName, 'w')
  f.write("\n".join(linesUpdated))
  f.flush()
  f.close()
 

def doLink(link, text, tag):

  newLink = ":ref:`" + text + " <" + tag + ">`"

  for root, dirnames, fileNames in os.walk(os.getcwd()):
    for fileName in fileNames:
      if scriptName in fileName:
        continue
      fileFixLink(root + "/" + fileName, link, newLink) 
      fileAddTag(root + "/" + fileName, text, tag)


def doFile(fileName):

  regex = r'`[\w\s+]*<#\w>`_'
  regex = r'`[^<]+<#\w*>'
  regexLink = r'`[^<`]+<#[\w-]*>`_'
  regexStrings = r'[^<>`]+'

  f = open(fileName, 'r')
  links = re.findall(regexLink, f.read()) #, re.M)
  for link in links:
    # Do not consider commented out lines
    if ".." in link:
      continue
    # In finding the link parts, remove the last "_" character
    linkParts = re.findall(regexStrings, link[:-1])
    linkText = linkParts[0].strip()
    linkTag = linkParts[1].strip()
    doLink(link, linkText, linkTag)
 
  f.close() 

# TODO eliminate ".." comments

def main():
  global linksChanged
  global tagsChanged

  for root, dirnames, fileNames in os.walk(os.getcwd()):
    for fileName in fileNames:
      if scriptName in fileName:
        continue
      doFile(root + "/" + fileName)


  print "Links changed: " + str(linksChanged)
  print "Tags changed: " + str(tagsChanged)
    
    
if __name__ == "__main__":
  main()

