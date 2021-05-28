// import native addon
const addonIdsIps = require('bindings')('idsips');

// expose module API
exports.firstAnalysis = addonIdsIps.firstAnalysis;
exports.allBlock = addonIdsIps.allBlock;
exports.allQuarantine = addonIdsIps.allQuarantine;
exports.folderAnalysis = addonIdsIps.folderAnalysis;
exports.removeAnalyseAndListeContamine = addonIdsIps.removeAnalyseAndListeContamine;