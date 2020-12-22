package com.example.backstage.Controller.InterviewController;

import com.example.backstage.Entity.InterviewEntity.Check;
import com.example.backstage.Entity.InterviewEntity.Interview;
import com.example.backstage.ResultVO;
import com.example.backstage.Service.InterviewService.CheckService;
import com.example.backstage.Service.InterviewService.InterviewService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import net.minidev.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

@Controller
@RequestMapping("/check")
@Api("验收")
@CrossOrigin
public class CheckController {
    @Autowired
    private CheckService service;
    @Autowired
    private InterviewService interviewService;

    /**
     *
     * @param check
     * @return
     */
    @RequestMapping(value = "/addCheck",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("新增验收")
    @ApiParam(name = "order",value = "订单信息",required = true)
    public ResultVO addCheck(@RequestBody Check check){
          String id=check.getId();
          try {
              interviewService.deleteById(id);
              service.addCheck(check);
              return ResultVO.SUCCESS("添加成功!");
          }catch (Exception e){
              return ResultVO.FAIL("新增失败!");
          }
    }

    /**
     *
     * @param check
     * @return
     */
    @RequestMapping(value = "/updateCheck",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("更新验收")
    @ApiParam(name = "order",value = "订单信息",required = true)
    public ResultVO updateCheck(@RequestBody Check check){
        try {
            service.addCheck(check);
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
    @ApiOperation("查询验收订单")
    @ApiParam(name = "all",value = "内容、页数、大小",required = true)
    public ResultVO addOrder(@RequestBody JSONObject object){
        String name=object.getAsString("all");
        int page=Integer.valueOf(object.getAsString("page"));
        int size=Integer.valueOf(object.getAsString("size"));
        Pageable pageable=new PageRequest(page,size);
        Page<Check> list=service.findAll(name,pageable);
        if (list.getTotalElements()==0){
            return ResultVO.SUCCESS();
        }else {
            return ResultVO.SUCCESS(list);
        }
    }
}
