package com.example.backstage.Controller.InterviewController;

import com.alibaba.fastjson.JSONObject;
import com.example.backstage.Entity.InterviewEntity.Interview;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

import java.math.BigDecimal;
import java.util.Date;

/** 
* InterviewController Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class InterviewControllerTest {
    @Autowired
    private MockMvc mvc;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: addOrder(@RequestBody Interview interview) 
* 
*/ 
@Test
public void testAddOrderInterview() throws Exception { 
//TODO: Test goes here...
    Interview interview=new Interview("123","201709000616","aef",new BigDecimal(20),new Date(),
            "1234567891234","hike",10,"");
    String json= JSONObject.toJSONString(interview);
    mvc.perform(MockMvcRequestBuilders.post("/interview/addOrder")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: updateOrder(@RequestBody Interview interview) 
* 
*/ 
@Test
public void testUpdateOrder() throws Exception { 
//TODO: Test goes here...
    Interview interview=new Interview("123","201709000616","aef",new BigDecimal(20),new Date(),
            "1234567891234","hikes",10,"");
    String json= JSONObject.toJSONString(interview);
    mvc.perform(MockMvcRequestBuilders.post("/interview/updateOrder")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: addOrder(@RequestBody JSONObject object) 
* 
*/ 
@Test
public void testAddOrderObject() throws Exception { 
//TODO: Test goes here...
    String str="{\"name\":\"\",\"page\":0,\"size\":10}";
    mvc.perform(MockMvcRequestBuilders.post("/interview/queryOrder")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(str)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: deleteOrder(@RequestBody Interview interview) 
* 
*/ 
@Test
public void testDeleteOrder() throws Exception { 
//TODO: Test goes here...
    Interview interview=new Interview();
    interview.setId("123");
    String json= JSONObject.toJSONString(interview);
    mvc.perform(MockMvcRequestBuilders.post("/interview/deleteOrder")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 
