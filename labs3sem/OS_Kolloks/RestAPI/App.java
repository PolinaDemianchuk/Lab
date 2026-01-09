package com.rest.crud;

import org.springframework.amqp.core.Queue;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cache.annotation.EnableCaching;
import org.springframework.context.annotation.Bean;

@SpringBootApplication
@EnableCaching
public class App
{
    @Bean
    public Queue myQueue()
    {
        return new Queue("task-queue", true);
    }
	public static void main(String[] args)
    {
		SpringApplication.run(App.class, args);
	}
}
