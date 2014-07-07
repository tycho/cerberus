name = "darwinian"
properties = {
    width = 31,
    height = 32,
    spritesheet = "darwinian.png",
    color = { 255, 255, 255 } --rgba values
}
behaviors = {
    "moveable",
    "render",
    "physics"
}

function onKeyDown(key)
    if key == 273 then -- SDLK_UP
        a = entity:GetProperty("velocity")
        if a == nil then
            a = Vector:new()
        end
        a.y = a.y - 10
        entity:SetProperty("velocity", a)
    elseif key == 274 then -- SDLK_DOWN
        a = entity:GetProperty("velocity")
        if a == nil then
            a = Vector:new()
        end
        a.y = a.y + 10
        entity:SetProperty("velocity", a)
    elseif key == 275 then -- SDLK_RIGHT
        a = entity:GetProperty("velocity")
        if a == nil then
            a = Vector:new()
        end
        a.x = a.x + 10
        entity:SetProperty("velocity", a)
    elseif key == 276 then -- SDLK_LEFT
        a = entity:GetProperty("velocity")
        if a == nil then
            a = Vector:new()
        end
        a.x = a.x - 10
        entity:SetProperty("velocity", a)
    elseif key <= 255 then
    end
end

function onKeyUp(key)
    if key == 273 then -- SDLK_UP
        a = entity:GetProperty("velocity")
        if a == nil then
            a = Vector:new()
        end
        a.y = a.y + 10
        entity:SetProperty("velocity", a)
    elseif key == 274 then -- SDLK_DOWN
        a = entity:GetProperty("velocity")
        if a == nil then
            a = Vector:new()
        end
        a.y = a.y - 10
        entity:SetProperty("velocity", a)
    elseif key == 275 then -- SDLK_RIGHT
        a = entity:GetProperty("velocity")
        if a == nil then
            a = Vector:new()
        end
        a.x = a.x - 10
        entity:SetProperty("velocity", a)
    elseif key == 276 then -- SDLK_LEFT
        a = entity:GetProperty("velocity")
        if a == nil then
            a = Vector:new()
        end
        a.x = a.x + 10
        entity:SetProperty("velocity", a)
    elseif key <= 255 then
    end
end
