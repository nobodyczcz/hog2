#-----------------------------------------------------------------------------
# GNU Makefile for static libraries: project dependent part
#
# $Id: Makefile.prj.inc,v 1.2 2006/11/01 19:16:13 nathanst Exp $
# $Source: /usr/cvsroot/project_hog/build/gmake/source/Makefile.prj.inc,v $
#-----------------------------------------------------------------------------

NAME = search
DBG_NAME = lib$(NAME).a
REL_NAME = lib$(NAME).a
DBG_SO_NAME = lib$(NAME).so
REL_SO_NAME = lib$(NAME).so

ROOT = ../../..
VPATH = $(ROOT)

DBG_OBJDIR = $(ROOT)/objs/$(NAME)/debug
REL_OBJDIR = $(ROOT)/objs/$(NAME)/release
DBG_BINDIR = $(ROOT)/bin/debug
REL_BINDIR = $(ROOT)/bin/release

PROJ_CXXFLAGS = -I$(ROOT)/abstraction -I$(ROOT)/simulation -I$(ROOT)/utils -I$(ROOT)/graph -I$(ROOT)/graphalgorithms  -I$(ROOT)/search
PROJ_DBG_CXXFLAGS = $(PROJ_CXXFLAGS)
PROJ_REL_CXXFLAGS = $(PROJ_CXXFLAGS)

PROJ_DBG_LNFLAGS =
PROJ_REL_LNFLAGS =

PROJ_DBG_LIB =
PROJ_REL_LIB =

default : all

SRC_CPP = search/ConstrainedEnvironment.cpp
