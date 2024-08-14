extends Node2D

var speed = 600
var direction = Vector2()
var lifetime = 1.5  

@onready var player1 = get_node("../Node2D/player1")
@onready var player2 = get_node("../Node2D/player2")

func _ready():
	set_physics_process(true)
	$Area2D/Timer.wait_time = lifetime
	$Area2D/Timer.start()

func _physics_process(delta):
	position += direction * speed * delta
	
func _on_timer_timeout():
	queue_free()

		



