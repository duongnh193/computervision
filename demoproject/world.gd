extends Node2D


const  SPEED = 300
var player1_direction = 1
var player2_direction = 1

var player1_hp = 100
var player2_hp = 100
var bullet_speed = 600
var bullet_timeout = 1.5

@onready var player1 = $player1
@onready var player2 = $player2
@onready var player1_hp_bar = $player1_hp
@onready var player2_hp_bar = $player2_hp
@onready var box = get_node("bounding_box/CollisionShape2D")
var Bullet = preload("res://bullet.tscn")

func _ready():
	player1_hp_bar.max_value = player1_hp
	player2_hp_bar.max_value = player2_hp
	player1_hp_bar.value = player1_hp
	player2_hp_bar.value = player2_hp
	

func _process(delta):
	handle_input(delta)
	update_hp()
	#decrease_hp(is_in_group("players_hp"),10)
	
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

	if player1_hp <= 0:
		print("Player 2 wins!")
		get_tree().quit()
	elif player2_hp <= 0:
		print("Player 1 wins!")
		get_tree().quit()

func decrease_hp(player, amount):
	if player == player1:
		player1_hp -= amount
	else:
		player2_hp -= amount

#func _on_area_2d_body1_entered(body):
	#if body.name == "Bullet":
		#get_tree().change_scene_to_file("res://main.tscn")
		#


#func _on_area_2d_body2_entered(body):
	#if body.name == "Bullet":
		#decrease_hp(player2_hp,10)
		
   
		
