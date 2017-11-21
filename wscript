## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

def build(bld):
    obj = bld.create_ns3_program('simulation', ['core',
                                                'point-to-point',
                                                'network',
                                                'applications',
                                                'internet'])
    obj.source = 'simulation.cc'
