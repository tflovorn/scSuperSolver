# Copyright (c) 2010 Timothy Lovorn
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

import os

import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter
from matplotlib.font_manager import FontProperties
from numpy import arange

import FileDict

niceLabels = {"d1": "$D_{1}$", "mu": "$\mu$", "f0": "$F_{0}$", "x": "$x$",
"tz": "$t_z$", "thp": "$t_{h}^{\prime}$"}

class Grapher(object):
    def __init__(self):
        # graphing parameter defaults
        self.axis_label_fontsize = 20
        self.num_ticks = 5
        self.tick_formatstr = "%.2f"

    def label(self, var):
        if var in niceLabels:
            return niceLabels[var]
        else:
            return var

    def readOutputs(self, configPaths):
        return [(filePath, 
            FileDict.readReferencedDict(filePath, "outputLogName")) 
            for filePath in configPaths]

    def extractVar(self, outputDataList, section, var):
        varValues = []
        for (fileName, outputData) in outputDataList:
            try:
                varValues.append(outputData.getLatestVar(section, var))
            except KeyError:
                print("warning: couldn't read var %s in section %s of file %s"
                      % (var, section, fileName))
        return varValues

    def plotSeriesDict(self, seriesDict, seriesLabel, xSection, xVar,
                       ySection, yVar, styles=None, legend_title=None):
        '''Create a plot of multiple series on the same axes in various styles.

        seriesDict's keys correspond to values of seriesLabel; the dict's
        values are lists of configs part of a single series.

        '''
        if styles is None:
            styles = ["k-", "r-", "g-", "b-", "c-", "m-", "y-"]
        fig, axes, bounds = None, None, None
        keys = sorted(map(float, seriesDict.keys()))
        for value, style in zip(keys, styles):
            configs = seriesDict[str(value)]
            label = "%s = %s" % (self.label(seriesLabel), value)
            fig, axes, bounds = self.simple2D(configs, xSection, xVar, 
                ySection, yVar, fig, axes, style, label, bounds)
        fontprop = FontProperties(size='large')
        axes.legend(loc=0, title=legend_title, prop=fontprop)
        return fig, axes
        

    def simple2D(self, configPaths, xSection, xVar, ySection, yVar, fig=None, 
                 axes=None, style="k-", label=None, bounds=None):
        '''Create a plot of a single series as 

        '''
        outputData = self.readOutputs(configPaths)
        xData = self.extractVar(outputData, xSection, xVar)
        yData = self.extractVar(outputData, ySection, yVar)
        # if either axes or figure is passed in as None, we ignore both
        if (fig is None) or (axes is None):
            fig = plt.figure()
            axes = fig.add_subplot(1,1,1)
        if bounds is None:
            bounds = [None, None]
        bounds = self.setxTicks(axes, xData, bounds)
        bounds = self.setyTicks(axes, yData, bounds)
        axes.plot(xData, yData, style, label=label)
        return fig, axes, bounds

    def setAxisLabels(self, axes, xLabel, yLabel):
        xLabel, yLabel = self.label(xLabel), self.label(yLabel)
        axes.set_xlabel(xLabel, fontsize=self.axis_label_fontsize)
        axes.set_ylabel(yLabel, fontsize=self.axis_label_fontsize)

    def setxTicks(self, axes, data, bounds):
        data = sorted(map(float, data))
        if bounds[0] is None:
            bounds[0] = [data[0], data[-1]]
        if data[0] < bounds[0][0]:
            bounds[0][0] = data[0]
        if data[-1] > bounds[0][1]:
            bounds[0][1] = data[-1]
        print("x bounds (%f, %f)" % (bounds[0][0], bounds[0][1]))
        axes.set_xticks(self.tickRange(bounds[0][0], bounds[0][1]))
        axes.xaxis.set_major_formatter(FormatStrFormatter(self.tick_formatstr))
        return bounds

    def setyTicks(self, axes, data, bounds):
        data = sorted(map(float, data))
        if bounds[1] is None:
            bounds[1] = [data[0], data[-1]]
        if data[0] < bounds[1][0]:
            bounds[1][0] = data[0]
        if data[-1] > bounds[1][1]:
            bounds[1][1] = data[-1]
        print("y bounds (%f, %f)" % (bounds[1][0], bounds[1][1]))
        axes.set_yticks(self.tickRange(bounds[1][0], bounds[1][1]))
        axes.yaxis.set_major_formatter(FormatStrFormatter(self.tick_formatstr))
        return bounds

    def tickRange(self, start, stop):
        step = (stop * 0.99 - start) / (self.num_ticks - 1)
        return arange(start, stop + step / 2.0, step)

    def saveFigure(self, fig, figurePath):
        fig.savefig(figurePath + ".png")
        fig.savefig(figurePath + ".eps")
