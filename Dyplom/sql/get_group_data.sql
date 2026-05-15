SELECT
        sg.StudentGroupID AS ID,
	s.SpecialityName AS Speciality,
    sg.GroupYear AS Year,
    sg.GroupNumber,
    qsg.QuantityStudent
    
FROM 
	studentgroup sg
    
JOIN 
	speciality s 
	        ON sg.SpecialityNumber = s.SpecialityNumber
        
JOIN
	quantitystudentongroup qsg
	        ON sg.StudentGroupID = qsg.StudentGroupID
        
WHERE
	qsg.SettingsYear = :yearConfig;