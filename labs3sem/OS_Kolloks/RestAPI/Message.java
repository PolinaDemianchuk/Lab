package com.rest.crud;

import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

@Service
public class Message
{
    @Autowired
    private RabbitTemplate rabbitTemplate;
    @Value("${app.rabbitmq.queue}")
    private String queue;
    public void sendTaskNotification(String message)
    {
        rabbitTemplate.convertAndSend(queue, message);
        System.out.println("Message was sent to queue: " + message);
    }
}