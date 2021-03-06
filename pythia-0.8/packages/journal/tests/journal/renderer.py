#!/usr/bin/env python
# 
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 
#                               Michael A.G. Aivazis
#                        California Institute of Technology
#                        (C) 1998-2005  All Rights Reserved
# 
#  <LicenseText>
# 
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 

import time
from journal.devices.Renderer import Renderer


class Logger(Renderer):


    def render(self, entry):
        meta = entry.meta
        meta["time"] = time.asctime()

        str = [
            '%(time)s -- %(facility)s [%(severity)s]' % meta
            ]

        for line in entry.text:
            str.append(self.format % line)

        return str


def test():
    import journal

    # install our renderer
    renderer = Logger()
    journal.journal().device.renderer = renderer

    info = journal.info("test")
    info.log("Hello world not!")
    info.activate()
    info.log("Hello world!")
    info.deactivate()
    info.log("Hello world again!")

    return


# main
if __name__ == "__main__":
    test()


# version
__id__ = "$Id: renderer.py,v 1.1.1.1 2005/03/08 16:13:53 aivazis Exp $"

#  End of file 
