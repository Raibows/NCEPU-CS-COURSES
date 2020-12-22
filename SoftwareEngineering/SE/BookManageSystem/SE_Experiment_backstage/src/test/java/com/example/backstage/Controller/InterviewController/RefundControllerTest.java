package com.example.backstage.Controller.InterviewController;

import com.alibaba.fastjson.JSONObject;
import com.example.backstage.Entity.InterviewEntity.Refund;
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
* RefundController Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class RefundControllerTest {
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
* Method: addRefund(@RequestBody Refund refund) 
* 
*/ 
@Test
public void testAddRefund() throws Exception { 
//TODO: Test goes here...
    Refund refund=new Refund("1234567890123","201709000616",new Date(),new BigDecimal(20),
            "as",10,false,"");
    String json= JSONObject.toJSONString(refund);
    mvc.perform(MockMvcRequestBuilders.post("/maintain/addRefund")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: findAll(@RequestBody JSONObject object) 
* 
*/ 
@Test
public void testFindAll() throws Exception { 
//TODO: Test goes here...
    String str="{\"all\":\"\",\"page\":0,\"size\":10}";
    mvc.perform(MockMvcRequestBuilders.post("/maintain/findAllRefund")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(str)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 
