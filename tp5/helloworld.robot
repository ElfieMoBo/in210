# Don't forget to put at least 2 spaces between a function and its args
*** Test Cases ***
test hello
  Log To Console   Hello World!

test keyword
    ${loc}   display   bye
    Log To Console   ${loc}
*** Keywords ***

display
  [Arguments]   ${item}
  Log To Console   ${item}
  RETURN   good: ${item} 

