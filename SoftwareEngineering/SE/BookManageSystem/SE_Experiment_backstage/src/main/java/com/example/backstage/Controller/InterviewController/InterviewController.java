package com.example.backstage.Controller.InterviewController;

import com.example.backstage.Entity.InterviewEntity.Interview;
import com.example.backstage.ResultVO;
import com.example.backstage.Service.InterviewService.InterviewService;
import com.example.backstage.Service.MatainService.BookService;
import com.example.backstage.Service.MatainService.UserService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import net.minidev.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.Date;

@Controller
@RequestMapping("/interview")
@Api("采访")
@CrossOrigin
public class InterviewController {
    @Autowired
    private InterviewService service;
    @Autowired
    private BookService bookService;
    @Autowired
    private UserService userService;

    /**
     *
     * @param interview
     * @return
     */
    @RequestMapping(value = "/addOrder",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("新增订单")
    @ApiParam(name = "interview", value = "订单信息", required = true)
    public ResultVO addOrder(@RequestBody Interview interview){
          String id=interview.getId();
          String isbn=interview.getIsbn();
          interview.setNum(10);
          Date date=new Date();
          interview.setOrderDate(date);
          if (bookService.findByIsbn(isbn)!=null){
              return ResultVO.SUCCESS("此书已存在!");
          }else {
              if (service.findInterviewById(id) != null) {
                  return ResultVO.SUCCESS("订单已存在!");
              } else {
                  service.addInterview(interview);
                  return ResultVO.SUCCESS("添加成功");
              }
          }
    }

    /**
     *
     * @param interview
     * @return
     */
    @RequestMapping(value = "/updateOrder",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("修改订单")
    @ApiParam(name = "interview",value = "采访内容",required = true)
    public ResultVO updateOrder(@RequestBody Interview interview){
        try {
            service.addInterview(interview);
            return ResultVO.SUCCESS("修改成功!");
        }catch (Exception e){
            return ResultVO.FAIL("修改失败!");
        }
    }

    /**
     *
     * @param object
     * @return
     */
    @RequestMapping(value = "/queryOrder",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("查询订单")
    @ApiParam(name = "all",value = "内容、页数、大小",required = true)
    public ResultVO addOrder(@RequestBody JSONObject object){
        String name=object.getAsString("name");
          int page=Integer.valueOf(object.getAsString("page"));
          int size=Integer.valueOf(object.getAsString("size"));
        Pageable pageable=new PageRequest(page,size);
        Page<Interview> list=service.findAll(name,pageable);
        if (list.getTotalElements()==0){
            return ResultVO.SUCCESS();
        }else {
            return ResultVO.SUCCESS(list);
        }
    }

    /**
     *
     * @param interview
     * @return
     */
    @RequestMapping(value = "/deleteOrder",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("删除订单")
    @ApiParam(name = "interview",value ="订单信息",required = true)
    public ResultVO deleteOrder(@RequestBody Interview interview){
        String id=interview.getId();
        try {
            service.deleteById(id);
            return ResultVO.SUCCESS("删除成功!");
        }catch (Exception e){
            return ResultVO.FAIL("删除失败!");
        }
    }
}
