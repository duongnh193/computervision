extends Node2D


const  SPEED = 300
var player1_direction = 1
var player2_direction = 1

var player1_hp = 100
var player2_hp = 100
var bullet_speed = 600
var bullet_timeout = 1.5
var close = false


@onready var player1 = $player1
@onready var player2 = $player2
@onready var player1_hp_bar = $player1_hp
@onready var player2_hp_bar = $player2_hp
var Bullet = preload("res://bullet.tscn")

#var shoot_position = player1.set_position(player1.position,false)
func _ready():
	player1_hp_bar.max_value = player1_hp
	player2_hp_bar.max_value = player2_hp
	player1_hp_bar.value = player1_hp
	player2_hp_bar.value = player2_hp
	print("from godot before call thread")
	$testcam.startThread()
	print("from godot call thread")
	pass

	

func _process(delta): 
	_enablecam()
	
	if($testcam.mySignalLeft()):
		shoot_left_when_open()
		
		
	if($testcam.mySignalRight()):
		shoot_right_when_open()
	
		
	handle_input(delta)
	update_hp()
	
func handle_input(delta):
	
	player1.position.y += player1_direction * SPEED * delta
	if player1.position.y <= player1_hp_bar.position.y + player1_hp_bar.size.y :
		player1.position.y = player1_hp_bar.position.y + player1_hp_bar.size.y
		player1_direction = 1
	elif player1.position.y >= get_viewport_rect().size.y - player1.size.y:
		player1.position.y = get_viewport_rect().size.y - player1.size.y
		player1_direction = -1
		
	player2.position.y += player2_direction * SPEED * delta
	if player2.position.y <= player2_hp_bar.position.y + player2_hp_bar.size.y:
		player2.position.y = player2_hp_bar.position.y + player2_hp_bar.size.y 
		player2_direction = 1
	elif player2.position.y >= get_viewport_rect().size.y - player2.size.y:
		player2.position.y = get_viewport_rect().size.y - player2.size.y
		player2_direction = -1
	
	
	if Input.is_action_just_pressed("shoot"):
		shoot_bullet(player2.position, Vector2(-1, 0))
	if Input.is_action_just_pressed("ui_select"):
		shoot_bullet(player1.position, Vector2(1, 0))
	
func shoot_bullet(start_position, direction):
	var bullet = Bullet.instantiate()
	bullet.position = start_position
	bullet.direction = direction
	bullet.speed = bullet_speed
	bullet.lifetime = bullet_timeout
	add_child(bullet)

func update_hp():
	player1_hp_bar.value = player1_hp
	player2_hp_bar.value = player2_hp

	if player1_hp == 0:
		print("Player 2 wins!")
		get_tree().quit()
	elif player2_hp == 0:
		print("Player 1 wins!")
		get_tree().quit()

func decrease_hp(player, amount):
	if player == player1:
		player1_hp -= amount
		player1_hp_bar.value = player1_hp
	else:
		player2_hp -= amount
		player2_hp_bar.value = player2_hp

func _enablecam():
	$player1.texture = $testcam.get_texture()
	$player2.texture = $testcam.get_texture()

func _on_area_1_body_entered(body):
	if body.name == "Bullet":
		decrease_hp(player1,10)
	pass # Replace with function body.


func _on_area_2_body_entered(body):
	if body.name == "Bullet":
		decrease_hp(player2,10)
	pass # Replace with function body.

func shoot_left_when_open():
	shoot_bullet(player2.position, Vector2(-1, 0))
	
func shoot_right_when_open():
	shoot_bullet(player1.position, Vector2(1, 0))

