*** Settings ***                                                                               
Library    RequestsLibrary                         

# Keeping history (and unique authentification)                                                                                                       
Suite Setup    Create Session  chuck  https://api.chucknorris.io/                  
                                                                                                       
*** Test Cases ***                                                                                     
                                                                                                       
Get Request Test                                                                                                                         
    ${resp_json} =   GET On Session   chuck  jokes/random   params=category=food                                  
    Log To Console   ${resp_json.json()}[value]

Get Specific Jokes 
    ${loc_joke}   Get Jokes From Category    animal
    Should Contain    ${loc_joke}  chuck  ignore_case=True
    Log To Console   ${loc_joke}

*** Keywords ***

Get Jokes From Category
    [Arguments]  ${category}
    ${resp_json} =   GET On Session   chuck  jokes/random   params=category=${category}   
    RETURN   ${resp_json.json()}[value]
