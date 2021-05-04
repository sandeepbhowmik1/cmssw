import FWCore.ParameterSet.Config as cms

from ..modules.correctedMulti5x5SuperClustersWithPreshower_cfi import *
from ..modules.multi5x5PreshowerClusterShape_cfi import *
from ..modules.uncleanedOnlyCorrectedMulti5x5SuperClustersWithPreshower_cfi import *
from ..modules.uncleanedOnlyMulti5x5SuperClustersWithPreshower_cfi import *

multi5x5PreshowerClusteringTask = cms.Task(
    correctedMulti5x5SuperClustersWithPreshower,
    multi5x5PreshowerClusterShape,
    uncleanedOnlyCorrectedMulti5x5SuperClustersWithPreshower,
    uncleanedOnlyMulti5x5SuperClustersWithPreshower
)
