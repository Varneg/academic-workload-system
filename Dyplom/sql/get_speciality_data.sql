SELECT  
    s.SpecialityNumber,
    d.DepartmentName,
    s.SpecialityName
FROM
    speciality s
    
JOIN
    department d
        ON s.DepartmentID = d.DepartmentID