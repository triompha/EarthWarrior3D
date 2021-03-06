
--------------------------------
-- @module TMXMapInfo
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setObjectGroups 
-- @param self
-- @param #array_table groups
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setTileSize 
-- @param self
-- @param #size_table tileSize
        
--------------------------------
--  initializes a TMX format with a  tmx file 
-- @function [parent=#TMXMapInfo] initWithTMXFile 
-- @param self
-- @param #string tmxFile
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- / map orientation
-- @function [parent=#TMXMapInfo] getOrientation 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- / is storing characters?
-- @function [parent=#TMXMapInfo] isStoringCharacters 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setLayers 
-- @param self
-- @param #array_table layers
        
--------------------------------
--  initializes parsing of an XML file, either a tmx (Map) file or tsx (Tileset) file 
-- @function [parent=#TMXMapInfo] parseXMLFile 
-- @param self
-- @param #string xmlFilename
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- / parent element
-- @function [parent=#TMXMapInfo] getParentElement 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setTMXFileName 
-- @param self
-- @param #string fileName
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] parseXMLString 
-- @param self
-- @param #string xmlString
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TMXMapInfo] getLayers
-- @param self
-- @return array_table#array_table ret (return value: array_table)

--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TMXMapInfo] getTilesets
-- @param self
-- @return array_table#array_table ret (return value: array_table)

--------------------------------
-- / parent GID
-- @function [parent=#TMXMapInfo] getParentGID 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setParentElement 
-- @param self
-- @param #int element
        
--------------------------------
--  initializes a TMX format with an XML string and a TMX resource path 
-- @function [parent=#TMXMapInfo] initWithXML 
-- @param self
-- @param #string tmxString
-- @param #string resourcePath
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setParentGID 
-- @param self
-- @param #int gid
        
--------------------------------
-- / layer attribs
-- @function [parent=#TMXMapInfo] getLayerAttribs 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- / tiles width & height
-- @function [parent=#TMXMapInfo] getTileSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] getTileProperties 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TMXMapInfo] getObjectGroups
-- @param self
-- @return array_table#array_table ret (return value: array_table)

--------------------------------
-- 
-- @function [parent=#TMXMapInfo] getTMXFileName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setCurrentString 
-- @param self
-- @param #string currentString
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setProperties 
-- @param self
-- @param #map_table properties
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setOrientation 
-- @param self
-- @param #int orientation
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setTileProperties 
-- @param self
-- @param #map_table tileProperties
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setMapSize 
-- @param self
-- @param #size_table mapSize
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setStoringCharacters 
-- @param self
-- @param #bool storingCharacters
        
--------------------------------
-- / map width & height
-- @function [parent=#TMXMapInfo] getMapSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setTilesets 
-- @param self
-- @param #array_table tilesets
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TMXMapInfo] getProperties
-- @param self
-- @return map_table#map_table ret (return value: map_table)

--------------------------------
-- 
-- @function [parent=#TMXMapInfo] getCurrentString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#TMXMapInfo] setLayerAttribs 
-- @param self
-- @param #int layerAttribs
        
--------------------------------
--  creates a TMX Format with a tmx file 
-- @function [parent=#TMXMapInfo] create 
-- @param self
-- @param #string tmxFile
-- @return TMXMapInfo#TMXMapInfo ret (return value: cc.TMXMapInfo)
        
--------------------------------
--  creates a TMX Format with an XML string and a TMX resource path 
-- @function [parent=#TMXMapInfo] createWithXML 
-- @param self
-- @param #string tmxString
-- @param #string resourcePath
-- @return TMXMapInfo#TMXMapInfo ret (return value: cc.TMXMapInfo)
        
--------------------------------
-- js ctor
-- @function [parent=#TMXMapInfo] TMXMapInfo 
-- @param self
        
return nil
